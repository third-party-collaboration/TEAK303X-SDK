/*
 $Id: oak3030_fan.c 2008-01-15 14:56:59 mark Hsieh $

 This code is used in the oak3030 series board with ITE8712 Super IO chipset.

  This code is to read the status of the fan speed.
  The oak3030 board works with Intel ATOM processor and ICH7 south bridge.
  All IO is configured by using the IO interface code of this driver.
  Application uses this driver to access the IO port.
  
  Create a device by using the command
   c- char device
    98 - major number
     0  - minor number
   #mknod /dev/fan c 98 0

 All rights are reserved.
 Mark Hsieh V1.00  2009/09/21 -- initial version
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
//#include <linux/gpio.h>
#include <linux/pci.h>
#include <linux/pci_ids.h>
#include <asm/io.h>
#include <asm/uaccess.h>
//#include <asm/msr.h>




#define ADDR_PORT	       	0x2E			// Address port
#define DATA_PORT	       	0x2F			// Data port

#define EC_ACTIVE          0x30        // EC activate register
#define EC_BASEADDR_REG	   0x60			// EC Base Address MSB Register
#define EC_BASEADDR1_REG	0x61			// EC Base Address LSB Register
#define FAN_MAIN_CTL       0x13        // EC fan main control
#define FAN_CTL            0x14        // EC fan control
#define FAN_16_COUNTER     0x0C        // EC enable 16-bit counter
#define FAN1               0x0D     // Fan Tachometer 1 reading register
#define FAN1E              0x18     // Fan Tachometer 1 extended reading register
#define EXIT_MODE		0x02			// Global Configure Control

#define FAN_MAJOR		  98

typedef unsigned char byte;


struct oak3030_fan_struct {
	int 		id;					  // id
	u16		BasePort;			// Base Address for LDN=0x04
	u16      AddrPort;       // Address Reg of the EC
   u16      DataPort;       // Data Reg. of the EC
};


#define LOCAL_VERSTRING 	"oak3030: 1.00"
static char *fan_version = "$Rev: 1.00$";
static char *fan_revdate = "$Date: 2009-09-21 14:56:59 +0100 $";
static char *fan_name= "oak3030_fan";

struct oak3030_fan_struct oak3030_fan_info;


inline static u16 io_read(unsigned char reg)
{
   outb(reg, oak3030_fan_info.AddrPort);
	return inb(oak3030_fan_info.DataPort);
}

inline static void io_write(unsigned char reg, unsigned char c)
{
   outb(reg, oak3030_fan_info.DataPort);
	outb(c, oak3030_fan_info.DataPort);
}

// set the enter key to configuration mode
// entry key= 0x87, 0x01, 0x55, 0x55 for 0x2E
static void fan_enterKey(void)
{
	outb(0x87, ADDR_PORT);
	outb(0x01, ADDR_PORT);
	outb(0x55, ADDR_PORT);
	outb(0x55, ADDR_PORT);
}

static void fan_setValue(byte reg, byte val)
{
	outb(reg, ADDR_PORT);
	outb(val, DATA_PORT);
}

static unsigned char fan_getValue(byte reg)
{
	outb(reg, ADDR_PORT);
	return inb(DATA_PORT);
}


static int fan_read(struct file *filp,char *buf,size_t count, loff_t *offset)
{
	u16 value;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	

	//printk("oak3030_fan: read minor id=%x\n", id);

	if(oak3030_fan_info.id != id)
	    return -1;
		
	//if (count == 0)
	//    return 0;

   value = (u16)io_read(FAN1E);    // bit 8-15
	value <<= 8;     // shift left
	value += (u16)io_read(FAN1);    // bit 0-7
	printk("oak3030_fan: get fan= 0x%0X\n", value);
	put_user(value, (u16 *)buf);

   return 1;
}


#if 0
static ssize_t fan_write(struct file *filp,const char *buf, size_t count,loff_t *offset)
{
	unsigned char kbuf[32];
//	unsigned char *p= kbuf;
	int i;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	


	if(oak3030_fan_info.id != id)
	    return -1;
		
	if (count == 0)
	    return 0;

	if(count > 32)
	    return -1;    // buffer full
	copy_from_user(kbuf, (unsigned char *)buf, count);

	//printk("oak3030_fan: output -> ");
	for(i=0; i < count; i++) {
		io_write(kbuf[i]);
		//printk("0x%X", kbuf[i]);
		//udelay(10);
	}
	//printk("\n");
	return count;
}
#endif

static int fan_open(struct inode *inode,  struct file * filp)
{
	unsigned char reg;
	unsigned short Port;
	unsigned char id1, id2;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );


	if(oak3030_fan_info.id != -1)   // device already open
		return -1;

	oak3030_fan_info.id= id;
//	printk("oak3030_fan: minor code=%d\n", id);

	// set enter key
	fan_enterKey();

	// Read the ID of ITE-8712
   	id1= fan_getValue(0x20);
   	id2= fan_getValue(0x21);
	printk("oak3030_fan: ID1=0x%X  ID2=0x%02X\n", id1, id2);

	// Choose logical device for Environment Controller
	// LDN= 0x04
	fan_setValue(0x07, 0x04);

   fan_setValue(EC_ACTIVE, 0x01);
	// Set Control Register of gpio to io base address
   Port= fan_getValue(EC_BASEADDR_REG) << 8;
   Port += fan_getValue(EC_BASEADDR1_REG);
	printk("oak3030_fan: base IO=0x%02X\n", Port);
	oak3030_fan_info.BasePort= Port;
	oak3030_fan_info.AddrPort= Port+0x05;	
	oak3030_fan_info.DataPort= Port+0x06;     

   // Fan 16-bit counter enable reg.
   reg= fan_getValue(FAN_16_COUNTER);   
  reg |= 0x01;       // enble fan_tac1 16-bit
  fan_setValue(FAN_16_COUNTER, reg);
	printk("oak3030_fan: enable 16-bit counter=0x%02X\n", reg);  

   reg= fan_getValue(FAN_MAIN_CTL);
   reg |= 0x10;   // fan man controller fan-1
   fan_setValue(FAN_CTL, reg);
   printk("oak3030_fan: fan_main_ctrl= 0x%02X\n", reg);
     
   // fan control register
   reg= fan_getValue(FAN_CTL);
   reg |= 0x01;   // mode control
   fan_setValue(FAN_CTL, reg);
   printk("oak3030_fan: fan_ctrl= 0x%02X\n", reg);
   
    // Exit the Configuration Mode for gpio
    // bit-1
    	fan_setValue(EXIT_MODE, 0x02);
   //	printk("oak3030_fan: init device exit\n");

	return 0;
}

static int fan_release(struct inode *inode, struct file * filp)
{
	if(oak3030_fan_info.id < 0)
		return -1;

	oak3030_fan_info.id= -1;
//	printk("oak3030_fan: device closed \n");
	return 0;
}

static void show_serial_version(void)
{
	printk("oak3030_fan: version %s (%s)\n",
	       fan_version, fan_revdate);
	return;
}

static struct file_operations oak3030_fan_fops = {
	.owner = THIS_MODULE,
//	.write = fan_write,
	.read = fan_read,
//	.ioctl = fan_ioctl,
	.open	= fan_open,
	.release= fan_release,
};

static int __init fan_init(void)
{
	int result;
	show_serial_version();
	oak3030_fan_info.id = -1;

	printk("oak3030_fan: module driver installed\n");
	if ((result= register_chrdev(FAN_MAJOR, fan_name, &oak3030_fan_fops)) < 0) {
		panic("oak3030_fan: Couldn't register ITE8712 PowerIO driver");
		return result;
	}
	return 0;
}

static void __exit fan_fini(void)
{
	//int ret;

	unregister_chrdev(FAN_MAJOR, fan_name);
	//if (ret < 0) 
 	//    printk("oak3030: failed to unregister ITE8712 GPIO driver (%d)\n", ret);
	//return;
}

module_init(fan_init);
module_exit(fan_fini);
MODULE_DESCRIPTION("OAK3030 (ITE8712 Super IO) fan IO driver");
MODULE_LICENSE("GPL");

