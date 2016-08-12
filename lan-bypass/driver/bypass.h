#ifndef _LINUX_LAN_BYPASS_H
#define _LINUX_LAN_BYPASS_H

#define BYPASS_MAJOR            31

#define GPIO_USE_SEL		0x00		// GPIO Use select Register
#define GPIO_IO_SEL			0x04		// GPIO I/O select regsiter
#define GP_LVL				0x0C		// GPIO Level for I/O Register
#define GPIO_USE_SEL2		0x30		// GPIO Use select 2 register [63:32]
#define GPIO_IO_SEL2		0x34		// GPIO I/O select 2 register [63:32]
#define GP_LVL2				0x38		// GPIO Level for I/O 2 register[63:32]

// LED System Status Indicator
// Use GPIO-25 to control the system status indicator LED


struct bypass_struct {
	int            	id;
	unsigned long		base;
	unsigned long		gpioL_out_val;
	unsigned long		gpioL_out_en;
	unsigned long		gpioH_out_val;
	unsigned long		gpioH_out_en;
};

#endif /* _LINUX_LAN_BYPASS_H */
