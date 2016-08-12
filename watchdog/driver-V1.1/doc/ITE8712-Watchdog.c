/* This code is a watch dog timer code for ITE8712 	*/
/* User can press keyboard, mouse to reset the watchdog timer
   Or programming the game port to reset the timer */

#include <stdio.h>

#define ADDR_PORT	        0x2E				// Address port
#define DATA_PORT	        0x2F				// Data port

#define WDC_CTRL_REG		0x71				// Control Register
#define WDC_CFG_REG			0x72				// Configuration Register
#define WDC_TIMEOUT_LSB		0x73				// Timer Time-Out LSB Register
#define WDC_TIMEOUT_MSB		0x74				// Timeer Time-Out MSB Register
#define WDC_EXIT_MODE			0x02

typedef unsigned char byte;

// set the enter key to configuration mode
// entry key= 0x87, 0x01, 0x55, 0x55 for 0x2E
void watchdog_enterKey(void)
{
	outp(ADDR_PORT, 0x87);
	outp(ADDR_PORT, 0x01);
	outp(ADDR_PORT, 0x55);
	outp(ADDR_PORT, 0x55);
}

void watchdog_setValue(byte reg, byte val)
{
	outp(ADDR_PORT, reg);
	outp(DATA_PORT, val);
}

main()
{
	// set enter key
	watchdog_enterKey();

	// Choose logical device for watchdog
	// LDN= 0x07
	watchdog_setValue(0x07, 0x07);
	

	// Set Control Register of watchdog to reset upon a KBC( mouse, keyboard, gameport) interrupt
	watchdog_setValue(WDC_CTRL_REG, 0x70);

	// Set watchdog time-Out value
	// LSB Register
	watchdog_setValue(WDC_TIMEOUT_LSB, 0x00);

	// MSB Register
	watchdog_setValue(WDC_TIMEOUT_MSB, 0x01);

	// Set Configuration Register to second-enabled
	// Output through KRST
	// Start watchdog
	watchdog_setValue(WDC_CFG_REG, 0xC0);

 	// Set Configuration Register to minute-enabled
	// Output through KRST
	// Start watchdog
	//watchdog_setValue(WDC_CFG_REG, 0x40);


	// Choose logical device for Game Port
	// LDN= 0x09
	watchdog_setValue(0x07, 0x09);
    // Enable Game Port function
	watchdog_setValue(0x30, 0x01);


    // Exit the Configuration Mode for watchdog
    // bit-1
    watchdog_setValue(WDC_EXIT_MODE, 0x02);
}

