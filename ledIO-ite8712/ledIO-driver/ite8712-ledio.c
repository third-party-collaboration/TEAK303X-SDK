/*
 $Id: oak3030_ledio.c 2008-01-15 14:56:59 mark Hsieh $

 This code is used in the oak3030 series board with ITE8712 Super IO chipset.

  This code is a LED status indicator control code, which use the GPIO-10 and GPIO-11 in Super I/O
  ITE8712 to control the LED on the board oak3030.
  The oak3030 board works with Intel ATOM processor and ICH7 south bridge.
  The GPIO default is set to low and output mode with base address 0x300.
  All IO is configured by using the IO interface code of this driver.
  Application uses this driver to access the IO port.

 All rights are reserved.
 Mark Hsieh V1.00  2009/04/27 -- initial version
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

#define GPIO_BASEADDR_REG	0x62			// IO Base Address MSB Register
#define GPIO_BASEADDR1_REG	0x63			// IO Base Address LSB Register
#define GPIO_SEL_REG		0x25			// GPIO set-1 Multi-Function Pin Selection Register
#define GPIO_POL_REG		0xB0			// GPIO set-1 polarity Register
#define GPIO_PULL_UP_REG	0xB8			// Pull-Up Register
#define GPIO_IO_MODE_REG	0xC0			// IO mode Register
#define GPIO_IO_REG			0xC8			// IO type Register; define input/output

#define GPIO_ESEL_REG		0x2A			// GPIO set-1 Extended Multi-Function Pin Selection Register

#define WDC_CTRL_REG		0x71			// Control Register
#define WDC_CFG_REG			0x72			// Configuration Register
#define WDC_TIMEOUT_LSB		0x73			// Timer Time-Out LSB Register
#define WDC_TIMEOUT_MSB		0x74			// Timeer Time-Out MSB Register
#define WDC_EXIT_MODE		0x02			// Global Configure Control

//#define GPIO_BASE			0x300			// IO base address
//#define GPIO_DATA_PORT		(GPIO_BASE)		// for GPIO set-1
#define GPIO_IO_C			0x55AA			// IO CTRL cmd

#define LEDIO_MAJOR		97

typedef unsigned char byte;


struct oak3030_ledio_struct {
	int 		id;					// id
	u16		Port_base;			// Port Base Address
     u16    DataPort;
//	unsigned char io;				// io type definition
};


#define LOCAL_VERSTRING 	"oak3030: 1.00"
static char *ledio_version = "$Rev: 1.00$";
static char *ledio_revdate = "$Date: 2008-03-24 14:56:59 +0100 $";
static char *ledio_name= "oak3030_ledio";

struct oak3030_ledio_struct oak3030_ledio_info;


inline static unsigned char io_read(void)
{
	return inb(oak3030_ledio_info.DataPort);
}

inline static void io_write(unsigned char c)
{
	//printk("ledio- Port= 0x%X c=%x\n", GPIO_DATA_PORT, c);
	outb(c, oak3030_ledio_info.DataPort);
}

// set the enter key to configuration mode
// entry key= 0x87, 0x01, 0x55, 0x55 for 0x2E
static void ledio_enterKey(void)
{
	outb(0x87, ADDR_PORT);
	outb(0x01, ADDR_PORT);
	outb(0x55, ADDR_PORT);
	outb(0x55, ADDR_PORT);
}

static void ledio_setValue(byte reg, byte val)
{
	outb(reg, ADDR_PORT);
	outb(val, DATA_PORT);
}

static unsigned char ledio_getValue(byte reg)
{
	outb(reg, ADDR_PORT);
   return inb(DATA_PORT);
}

#if 0
static int ledio_read(struct file *filp,char *buf,size_t count, loff_t *offset)
{
	unsigned int value;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	

	//printk("oak3030_ledio: read minor id=%x\n", id);

	if(oak3030_ledio_info.id != id)
	    return -1;
		
	//if (count == 0)
	//    return 0;

   	value = io_read();
	value &= 0x04;
	value >>= 2;
	//printk("oak3030_ledio: get io= 0x%02X\n", value);
	put_user(value, (unsigned char *)buf);

   return 1;
}
#endif

static ssize_t ledio_write(struct file *filp,const char *buf, size_t count,loff_t *offset)
{
	unsigned char kbuf[32];
//	unsigned char *p= kbuf;
	int i;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	


	if(oak3030_ledio_info.id != id)
	    return -1;
		
	if (count == 0)
	    return 0;

	if(count > 32)
	    return -1;    // buffer full
	copy_from_user(kbuf, (unsigned char *)buf, count);

	//printk("oak3030_ledio: output -> ");
	for(i=0; i < count; i++) {
		io_write(kbuf[i]);
		//printk("0x%X", kbuf[i]);
		//udelay(10);
	}
	//printk("\n");
	return count;
}

static int ledio_open(struct inode *inode,  struct file * filp)
{
	//unsigned char set;
	unsigned short Port;
	unsigned char id1, id2;
	unsigned char v, v1;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );


	if(oak3030_ledio_info.id != -1)   // device already open
		return -1;

	oak3030_ledio_info.id= id;
//	printk("oak3030_ledio: minor code=%d\n", id);

	// set enter key
	ledio_enterKey();

	// Read the ID of ITE-8712
   	id1= ledio_getValue(0x20);
   	id2= ledio_getValue(0x21);
	printk("oak3030_ledio: ID1=0x%X  ID2=0x%X\n", id1, id2);

	// Choose logical device for gpio
	// LDN= 0x07
	ledio_setValue(0x07, 0x07);

	// Set Control Register of gpio to io base address
    Port= ledio_getValue(GPIO_BASEADDR_REG) << 8;
    Port += ledio_getValue(GPIO_BASEADDR1_REG);
	printk("oak3030_gpio: base IO=0x%X\n", Port);
	oak3030_ledio_info.Port_base= Port;
	oak3030_ledio_info.DataPort= Port;     
	//oak3030_ledio_info.Port_base= Port= GPIO_BASE;
	//ledio_setValue(GPIO_BASEADDR_REG, (Port >> 8) & 0xFF);   // IO base MSB Register
	//ledio_setValue(GPIO_BASEADDR1_REG, Port & 0xFF);	     // IO base LSB Register
//	printk("oak3030_ledio: GPIO base=0x%x\n", Port);

	// Set GPIO set-1 extended multi-function pins to GPIO 
	v= ledio_getValue(GPIO_ESEL_REG);
	//printk("ledio: extended multi-f=0x%x\n", v);
	v |= 0x03;  	// set bit-0, 1 for gpio-10, 11
	ledio_setValue(GPIO_ESEL_REG, v);
	v= ledio_getValue(GPIO_ESEL_REG);
//	printk("ledio: extended mf=0x%x\n", v);

	// Set GPIO set-1 multi-function pins to GPIO 
	v= ledio_getValue(GPIO_SEL_REG);
//	printk("ledio: set-1 mf=0x%x\n", v);
	v |= 0x03;  	// gpio-10, 11
	ledio_setValue(GPIO_SEL_REG, v);
	v= ledio_getValue(GPIO_SEL_REG);
//	printk("ledio: rd set-1 mf=0x%x\n", v);

	// Set GPIO set-1 to non-inverting
	v= ledio_getValue(GPIO_POL_REG) & 0xFC;   // clear bit-2
	ledio_setValue(GPIO_POL_REG, v);

 	// Set GPIO set-1 Internal pull-up(latch) Register
	v= ledio_getValue(GPIO_PULL_UP_REG) | 0x03;   // AP toggle the LED status
	ledio_setValue(GPIO_PULL_UP_REG, v);	 // enabled 

	// Set GPIO set-1 to IO type
	v= ledio_getValue(GPIO_IO_REG) | 0x03;   // output for bit-0, 1
	//oak3030_ledio_info.io= v;  
	ledio_setValue(GPIO_IO_REG, v);   // output direction

	// Set GPIO set-1 to IO mode Enabled
	v= ledio_getValue(GPIO_SEL_REG) | 0x03;	// enable the gpio function
	ledio_setValue(GPIO_IO_MODE_REG, v);

    // Exit the Configuration Mode for gpio
    // bit-1
    	ledio_setValue(WDC_EXIT_MODE, 0x02);
//	printk("oak3030_ledio: init device exit\n");

	return 0;
}

static int ledio_release(struct inode *inode, struct file * filp)
{
	if(oak3030_ledio_info.id < 0)
		return -1;

	oak3030_ledio_info.id= -1;
//	printk("oak3030_ledio: device closed \n");
	return 0;
}

static void show_serial_version(void)
{
	printk("oak3030_ledio: version %s (%s)\n",
	       ledio_version, ledio_revdate);
	return;
}

static struct file_operations oak3030_ledio_fops = {
	.owner = THIS_MODULE,
	.write = ledio_write,
//	.read = ledio_read,
//	.ioctl = ledio_ioctl,
	.open	= ledio_open,
	.release= ledio_release,
};

static int __init ledio_init(void)
{
	int result;
	show_serial_version();
	oak3030_ledio_info.id = -1;

	printk("oak3030_ledio: module driver installed\n");
	if ((result= register_chrdev(LEDIO_MAJOR, ledio_name, &oak3030_ledio_fops)) < 0) {
		panic("oak3030_ledio: Couldn't register ITE8712 PowerIO driver");
		return result;
	}
	return 0;
}

static void __exit ledio_fini(void)
{
	//int ret;

	unregister_chrdev(LEDIO_MAJOR, ledio_name);
	//if (ret < 0) 
 	//    printk("oak3030: failed to unregister ITE8712 GPIO driver (%d)\n", ret);
	//return;
}

module_init(ledio_init);
module_exit(ledio_fini);
MODULE_DESCRIPTION("OAK20x0 (ITE8712 Super IO) led IO driver");
MODULE_LICENSE("GPL");

