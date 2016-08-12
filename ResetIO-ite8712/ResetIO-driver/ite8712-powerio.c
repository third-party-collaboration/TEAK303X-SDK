/*
 $Id: oak3030_powerio.c 2008-01-15 14:56:59 mark Hsieh $

 This code is used in the oak3030 series board with ITE8712 Super IO chipset.

  This code is a Power GPIO-52 device driver used to read/write GPIO set 5 in ITE-8712.
  The oak3030 board works with Intel ATOM processor and ICH7 south bridge.
  The GPIO default is set to low and output mode with base address 0x300.
  All IO is configured by using the IO interface code of this driver.
  Application uses this driver to access the IO port.

 All rights are reserved.
 Mark Hsieh V1.00  2008/03/21 -- initial version
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
#define GPIO_SEL_REG		0x29			// GPIO set-5 Multi-Function Pin Selection Register
#define GPIO_POL_REG		0xB4			// GPIO set-5 polarity Register
#define GPIO_PULL_UP_REG	0xBC			// Pull-Up Register
#define GPIO_IO_MODE_REG	0xC4			// IO mode Register
#define GPIO_IO_REG			0xCC			// IO type Register

#define WDC_CTRL_REG		0x71			// Control Register
#define WDC_CFG_REG			0x72			// Configuration Register
#define WDC_TIMEOUT_LSB		0x73			// Timer Time-Out LSB Register
#define WDC_TIMEOUT_MSB		0x74			// Timeer Time-Out MSB Register
#define WDC_EXIT_MODE		0x02			// Global Configure Control

//#define GPIO_BASE			0x300			// IO base address
//#define GPIO_DATA_PORT		(GPIO_BASE+4)		// for GPIO set-5
#define GPIO_IO_C			0x55AA			// IO CTRL cmd

#define POWERIO_MAJOR		98

typedef unsigned char byte;


struct oak20x0_powerio_struct {
	int 		id;					// id
	u16		Port_base;			// Port Base Address
    u16     DataPort;           // Data Port based on BASE IO
//	unsigned char io;				// io type definition
};


#define LOCAL_VERSTRING 	"oak20x0: 1.00"
static char *powerio_version = "$Rev: 1.00$";
static char *powerio_revdate = "$Date: 2008-01-15 14:56:59 +0100 (Tues., 13 Feb. 2007) $";
static char *powerio_name= "oak20x0_powerio";

struct oak20x0_powerio_struct oak20x0_powerio_info;


inline static unsigned char io_read(void)
{
	return inb(oak20x0_powerio_info.DataPort);
}

inline static void io_write(unsigned char c)
{
	outb(c, oak20x0_powerio_info.DataPort);
}

// set the enter key to configuration mode
// entry key= 0x87, 0x01, 0x55, 0x55 for 0x2E
static void powerio_enterKey(void)
{
	outb(0x87, ADDR_PORT);
	outb(0x01, ADDR_PORT);
	outb(0x55, ADDR_PORT);
	outb(0x55, ADDR_PORT);
}

static void powerio_setValue(byte reg, byte val)
{
	outb(reg, ADDR_PORT);
	outb(val, DATA_PORT);
}

static unsigned char powerio_getValue(byte reg)
{
	outb(reg, ADDR_PORT);
   return inb(DATA_PORT);
}

static int powerio_read(struct file *filp,char *buf,size_t count, loff_t *offset)
{
	unsigned int value;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );	

	//printk("oak20x0_powerio: read minor id=%x\n", id);

	if(oak20x0_powerio_info.id != id)
	    return -1;
		
	//if (count == 0)
	//    return 0;

   	value = io_read();
	value &= 0x04;
	value >>= 2;
	//printk("oak20x0_powerio: get io= 0x%02X\n", value);
	put_user(value, (unsigned char *)buf);

   return 1;

}


static int powerio_open(struct inode *inode,  struct file * filp)
{
	//unsigned char set;
	unsigned short Port;
	unsigned char id1, id2;
	unsigned char v;
	int id= MINOR( filp->f_dentry->d_inode->i_rdev );


	if(oak20x0_powerio_info.id != -1)   // device already open
		return -1;

	oak20x0_powerio_info.id= id;
	printk("oak20x0_powerio: minor code=%d\n", id);

	// set enter key
	powerio_enterKey();

	// Read the ID of ITE-8712
   	id1= powerio_getValue(0x20);
   	id2= powerio_getValue(0x21);
	printk("oak20x0_powerio: ID1=0x%X  ID2=0x%X\n", id1, id2);

	// Choose logical device for gpio
	// LDN= 0x07
	powerio_setValue(0x07, 0x07);


	// Set Control Register of gpio to io base address
    Port= powerio_getValue(GPIO_BASEADDR_REG) << 8;
    Port += powerio_getValue(GPIO_BASEADDR1_REG);
	printk("oak3030_gpio: base IO=0x%X\n", Port);
	oak20x0_powerio_info.Port_base= Port;
	oak20x0_powerio_info.DataPort= (Port+4);
	//oak20x0_powerio_info.Port_base= Port= GPIO_BASE;
	//powerio_setValue(GPIO_BASEADDR_REG, (Port >> 8) & 0xFF);   // IO base MSB Register
	//powerio_setValue(GPIO_BASEADDR1_REG, Port & 0xFF);		   // IO base LSB Register

	// Set GPIO set-5 multi-function pins to GPIO 
	v= powerio_getValue(GPIO_SEL_REG) | 0x04;
	powerio_setValue(GPIO_SEL_REG, v);

	// Set GPIO set-5 to non-inverting
	v= powerio_getValue(GPIO_POL_REG) & 0xFB;   // clear bit-2
	powerio_setValue(GPIO_POL_REG, v);

 	// Set GPIO set-5 Internal pull-up(latch) Register
	v= powerio_getValue(GPIO_PULL_UP_REG) | 0x04;
	powerio_setValue(GPIO_PULL_UP_REG, v);	 // enabled 

	// Set GPIO set-5 to IO type
	v= powerio_getValue(GPIO_IO_REG) & 0xFB;   // input for bit-2
	//oak20x0_powerio_info.io= v;  
	powerio_setValue(GPIO_IO_REG, v);   // output direction

	// Set GPIO set-5 to IO mode Enabled
	v= powerio_getValue(GPIO_SEL_REG) | 0x04;
	powerio_setValue(GPIO_IO_MODE_REG, v);

    // Exit the Configuration Mode for gpio
    // bit-1
    	powerio_setValue(WDC_EXIT_MODE, 0x02);
	printk("oak20x0_powerio: init device exit\n");

	return 0;
}

static int powerio_release(struct inode *inode, struct file * filp)
{
	if(oak20x0_powerio_info.id < 0)
		return -1;

	oak20x0_powerio_info.id= -1;
	printk("oak20x0_powerio: device closed \n");
	return 0;
}

static void show_serial_version(void)
{
	printk("oak20x0_powerio: version %s (%s)\n",
	       powerio_version, powerio_revdate);
	return;
}

static struct file_operations oak20x0_powerio_fops = {
	.owner = THIS_MODULE,
//	.write = powerio_write,
	.read = powerio_read,
//	.ioctl = powerio_ioctl,
	.open	= powerio_open,
	.release= powerio_release,
};

static int __init powerio_init(void)
{
	int result;
	show_serial_version();
	oak20x0_powerio_info.id = -1;

	printk("oak20x0_powerio: module driver installed\n");
	if ((result= register_chrdev(POWERIO_MAJOR, powerio_name, &oak20x0_powerio_fops)) < 0) {
		panic("oak20x0_powerio: Couldn't register ITE8712 PowerIO driver");
		return result;
	}
	return 0;
}

static void __exit powerio_fini(void)
{
	//int ret;

	unregister_chrdev(POWERIO_MAJOR, powerio_name);
	//if (ret < 0) 
 	//    printk("oak20x0: failed to unregister ITE8712 GPIO driver (%d)\n", ret);
	//return;
}

module_init(powerio_init);
module_exit(powerio_fini);
MODULE_DESCRIPTION("OAK20x0 (ITE8712 Super IO) PowerIO driver");
MODULE_LICENSE("GPL");

