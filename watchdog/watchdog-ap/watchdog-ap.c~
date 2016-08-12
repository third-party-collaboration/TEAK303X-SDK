/* This is a watchdog testing code. */
/* 1. Create a watchdog device in /dev directory with major 10 */
/*      #mknod watchdog c 10 130 
	2. Operation
		# E -- Enable the watchdog function
		# R -- Reset the wathcdog function
		# D -- Disable the watchdog function
		# C -- Close function
		# T -- TimeOut Counter
		# G -- Get timeOut Counter
		# Q -- Quit program
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>				
#include <sys/types.h>			
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	
#include <sys/ioctl.h>
#include <termios.h>
#include <linux/types.h>
#include <linux/watchdog.h>
typedef	unsigned int 		u32;
typedef	unsigned short		u16;

/******************************************************************
* Prototype
******************************************************************/

/* The following three statements are defined in key.c */
extern int stdin_init(int);
extern int stdin_read(char *c, int fd);
void set_timer_vector(void);

char Version[]= "V1.10";

/* Start the interrupt-driven serial I/O */
main(int argc, char *argv[]){
	unsigned char c, b;
	int  datafound;
	int ret, i;
	int quit;
//	int readStatus= 0;
//	u32	regVal[4];
//	u32	msrReg;
	unsigned int set;
	static int status= 0;
	unsigned char buf[80];
	//u32		val[2];
	unsigned char *p=buf;
	//int TxSize;
	int fd;
	u16 TimeOut_Counter=0;
	
    printf("watchdog-ap: Start Watchdog-AP \n");
 
	fd= open("/dev/watchdog", O_RDWR);
	// Start the Net
	if(fd < 0) {
		printf("watchdog-ap:  Can not open device driver\n");
		exit(0);	
	}
	printf("watchdog-ap: open success fd=%X\n", fd);
	//set_timer_vector();
	//if(stdin_init(fileno(stdin)) < 0)
	//	printf("watchdog-ap: stdin set non-blocking err\n");	
		
	printf("watchdog-ap: watchdog AP\n");

	quit= 0;
	datafound= 0;
	status= 0x01;
	c= b= 0;

	while(!quit) {
        c= 0;

		ret=stdin_read((char *)&c, fileno(stdin));
		//printf("ret=%d C=%X\n", ret, c);
		if( c == 0x0A) 
		    continue;
		
		if(ret > 0) {
			switch(c) {
				case 'Q':
					quit= 1;
					if(status & 0x01) {
						close(fd);
						status= 0x02;
					}
					break;
      			case 0x0A:      // return code
					break;
				case 'O':
					fd= open("/dev/watchdog", O_RDWR);
					if(fd <= 0)
						printf("watchdog-ap: Can not open watchdog device, error=%d\n", fd);
					else {
						printf("watchdog-ap: Open success code=%d\n", fd);
						status= 0x01;
					}
					break;
				case 'C':
					if(status & 0x01) {
						close(fd);
						status= 0x02;
					}
					break;
				case 'R':   // Reset  
					//set= WATCHDOG_RESET;
					set= WDIOC_KEEPALIVE;
					ioctl(fd, set, 0);
					break;
				case 'E':   // enable watchdog
					set= WDIOS_ENABLECARD;
					ioctl(fd, set, 0);
					break;
				case 'D':   // disable watchdog
					set= WDIOS_DISABLECARD;
					ioctl(fd, set, 0);
					printf("disable watchdog\n");
					break;
				case 'G':   // Get watchdog TimeOut Counter
					set= WDIOC_GETTIMEOUT;
					ioctl(fd, set, &TimeOut_Counter);
					printf("timeOut hex counter= 0x%X\n", TimeOut_Counter);
					break;
				case 'T':
					p=buf;
					set= 0;
					printf("ap:timeOut hex counter=");
					scanf("%X", &set);
					*(u16 *)p= (u16)set;
 					//ioctl(fd, WATCHDOG_COUNTER, (unsigned long)buf);
					set= WDIOC_SETTIMEOUT;
 					ioctl(fd, set, (unsigned long)buf);
					break;
				default:
				    break;

			}
		}
	}	// while loop
	return 0;
}
