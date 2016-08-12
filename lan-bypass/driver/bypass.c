/*
  This is a bypass driver used in the Teak3020 product of ARinfotek Inc., Taiwan. 
  This code is to access the specified I/O port, 0x2A0 or 0x2A1, to read/write control data 
  Index Port= 0x200
  Data Port= 0x201
  For more detail spec., please read the ANSA3020 Bypass Sepc. from the ARinfotek Inc.

  All rights are reserved by ARinfotek Inc.
  Mark Hsieh V1.0.0  2007/03/21 -- initial version
  Mark Hsieh V1.0.1  2009/05/27 -- update the base address= 0x200
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/pci_ids.h>
#include <asm/io.h>
#include <asm/uaccess.h>



#if 0
#define DEBUG_ON
#endif

#define LOCAL_VERSTRING 	""
static char *bypass_version = "1.00";
static char *bypass_revdate = "2009-01-16";
static char *bypass_name = "3020-bypass";

#define BYPASS_MAJOR            31


#define IDXPORT				0x200
#define DATAPORT			0x201
#define BYPASS_TIMER_REG	0xA0
#define BYPASS_CTRL_REG		0xA1

static u8 bypass_timer= 0;
static u8 bypass_ctrl= 0;

static int bypass_id= -1;
char Version[]= "V1.00";

static inline void wr_ctrl_reg(u8 c)
{
	outb(BYPASS_CTRL_REG, IDXPORT);
	outb(c, DATAPORT);
}

static u8 rd_ctrl_reg(void)
{
	outb(BYPASS_CTRL_REG, IDXPORT);
	return inb(DATAPORT);
}

static inline void wr_timer_reg(u8 c)
{
	outb(BYPASS_TIMER_REG, IDXPORT);
	outb(c, DATAPORT);
}

static u8 rd_timer_reg(void)
{
	outb(BYPASS_TIMER_REG, IDXPORT);
	return inb(DATAPORT);
}


static void init_bypass(void)
{
	// set bypass to normal state
	wr_ctrl_reg(0);
	wr_timer_reg(0);
	bypass_ctrl= 0;
	bypass_timer= 0;
}



static inline void bypass_enabled_immediately(void)
{
	if(bypass_ctrl & 0x04) {
		bypass_ctrl &= 0xE7;
		bypass_ctrl |= 0x14;
		printk("bypass: enable immediately= 0x%X\n", bypass_ctrl);
		wr_ctrl_reg(bypass_ctrl);
	}
}

static inline void bypass_back2Normal(void)
{
	bypass_ctrl &= 0xE7;
	bypass_ctrl |= 0x08;
	wr_ctrl_reg(bypass_ctrl);	
}

static inline void bypass_disabled(void)
{
	bypass_ctrl &= 0xFB;		// disable bypass 
	bypass_back2Normal();
}
static inline void bypass_timerCtrl(void)
{
	if(bypass_ctrl & 0x04) {
		bypass_ctrl &= 0xE7;
		bypass_ctrl |= 0x1C;		// timer control
		printk("bypass: timerCtrl=0x%X\n", bypass_ctrl); 
		wr_ctrl_reg(bypass_ctrl);	
	}
}

static void bypass_timerSetting(u8 tCode)
{
	tCode &= 0x0F;
	if(tCode != 0) {
		bypass_timer &= 0xF0;
		bypass_timer |= 0x40 | tCode;		// timer setting
		printk("bypass: enable timer setting=0x%X\n", bypass_timer);
		wr_timer_reg(bypass_timer);
	}
}
static void bypass_disable_timer(void)
{
	bypass_timer &= 0xBF;
	wr_timer_reg(bypass_timer);	
}
static u8 check_timer_status(void)
{
	if(rd_timer_reg() & 0x80)
		return 1; 		// printf("Timer is TimeOut\n");
	else
		return 0;		// printf("Timer is counting\n");
}

static void bypass_set_poweroff(u8 c)
{
	if(bypass_ctrl & 0x04) {
		bypass_ctrl |= c & 0x03;
		wr_ctrl_reg(bypass_ctrl);
	}
}

/*
inline void bypass_poweroff(void)
{
	bypass_ctrl &= 0xFC;
	bypass_ctrl |= 0x01;	// bypass when power off
	wr_ctrl_reg(bypass_ctrl);	
}
*/
static void bypass_preState(void)
{
	if(bypass_ctrl & 0x04) {
		bypass_ctrl &= 0xE7;
		bypass_ctrl |= 0x04;	// bypass keep pre_state
		wr_ctrl_reg(bypass_ctrl);
	}
}

static u8 check_bypass_status(void)
{
	if(rd_ctrl_reg() & 0x80)
		return 1;		//printf("Current state is BYPASS\n");
	else
		return 0;		//printf("Current state is NORMAL\n");
}


/*
	input unsigned char:  0x10  Get bypass status
						  0x00  Get timer status
*/
static int bypass_read(struct file *filp,char *buf,size_t count,loff_t *offset)
{
	u8 reg=0;
	u8 ret=0;

	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	

	if(bypass_id != id)
	    return -1;
		
	if (count == 0)
	    return 0;

	get_user(reg,(u8 *)buf);
	if(reg & 0xF0)     // Get bypass status
		ret= check_bypass_status();  // 1: bypass mode  0: normal mode
	else   	   // Get timeout status
		ret= check_timer_status();	 // 1: timeout  0: counting

	put_user(ret, (u8 *)buf);
	
   return 1;

}


static ssize_t bypass_write(struct file *filp,const char *buf,size_t count,loff_t *offset)
{
	unsigned short setValue=0;
	u8 ctrl_reg;
	u8 timer_reg;
	u8 bypass_pwr;
	u8 bypass_type;
	//u8 timer= 0;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	

	if(bypass_id != id)
	    return -1;
		
	if (count == 0)
	    return 0;

	get_user(setValue,(unsigned short *)buf);
	ctrl_reg= (u8)(setValue & 0x00FF);
	timer_reg= (u8)(setValue >> 8) & 0xFF;

	if(ctrl_reg & 0x04) 
		bypass_ctrl |= 0x04;		// enable bypass function
	else {
		bypass_ctrl &= 0xFB;		// clear bypass function
		bypass_back2Normal();
		if(timer_reg == 0)
			return 1;
	}
	bypass_pwr=	(ctrl_reg & 0x03);
	bypass_set_poweroff(bypass_pwr);

	printk("bypass: ctrl_reg=0x%X\n", ctrl_reg);
	bypass_type= (ctrl_reg >> 3) & 0x03;
	printk("bypass: bypass type=%d\n", bypass_type);

	switch(bypass_type) {
		case 0:		// keep pre-state
			bypass_preState();
			break;
		case 1:		// back to normal
			bypass_back2Normal();
			break;
		case 2:		// immediately bypass
			bypass_enabled_immediately();
			break;
		case 3:		// timer control
			bypass_timerSetting(timer_reg);
			bypass_timerCtrl();
			break;
	}

	return 1;
}

/*
static int bypass_ioctl(struct inode *inode, struct file *file,
			    unsigned int cmd, unsigned long arg)
{
	return 0;
}
*/

static int bypass_open(struct inode *inode,  struct file * filp)
{
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );

	if(bypass_id != -1)   // device already open
		return -1;

	bypass_id= id;
	init_bypass();
	return 0;
}

static int bypass_release(struct inode *inode, struct file * filp)
{
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	

	if(bypass_id != id)
	    return -1;

	bypass_id= -1;
	return 0;

}

static char bypass_options[] __initdata = "No options\n";

static void show_serial_version(void)
{
	printk(KERN_INFO "%s version %s%s (%s) with%s", bypass_name,
	       bypass_version, LOCAL_VERSTRING, bypass_revdate,
	       bypass_options);
	return;
}

static struct file_operations bypass_fops = {
	.read	= bypass_read,
	.write	= bypass_write,
//	.ioctl= bypass_ioctl,
	.open	= bypass_open,
	.release= bypass_release,
};
	
static int __init bypass_init(void)
{
	int result;

	show_serial_version();

	bypass_id= -1;
	if ((result= register_chrdev(BYPASS_MAJOR, bypass_name, &bypass_fops)) < 0) {
		panic("bypass: Teak-3020 Couldn't register bypass driver");
						return result;
	}
	printk("bypass: Teak-3020 module driver installed\n");
	return 0;
}

static void __exit bypass_fini(void)
{
	int e1;

	if ((e1 = unregister_chrdev(BYPASS_MAJOR, bypass_name)) < 0) 
		printk("bypass: failed to unregister bypass driver (%d)\n",  e1);
	return ;
}

module_init(bypass_init);
module_exit(bypass_fini);
MODULE_DESCRIPTION("LAN bypass Driver");
MODULE_LICENSE("GPL");
