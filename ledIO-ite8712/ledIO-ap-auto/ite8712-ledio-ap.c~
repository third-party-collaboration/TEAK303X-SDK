/* This is a gpio testing code. */
/* 1. Create a gpio device in /dev directory with major 95 */
/*      #mknod /dev/led c 97 0 
	2. Operation
		# w -- Write GPIO function
		# t -- Toggle LED auto running
		# ? -- help
		# q -- Quit program
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
//#include <linux/watchdog.h>
typedef	unsigned int 		u32;
typedef	unsigned short		u16;


extern int ledtimer;

/******************************************************************
* Prototype
******************************************************************/

/* The following three statements are defined in key.c */
extern int stdin_init(int);
extern int stdin_read(char *c, int fd);
void set_timer_vector(void);

char Version[]= "V1.00";

/* Start the interrupt-driven serial I/O */
main(int argc, char *argv[]){
	int quit;
	int fd;
	int autoled= 0;
	int Index= 0;
	unsigned char b;
	
    printf("ledIO: Start LED IO Application \n");
 
	fd= open("/dev/ledio", O_RDWR);
	// Start the Net
	if(fd < 0) {
		printf("ledIO:  Can not open device driver\n");
		exit(0);	
	}
	//printf("ledIO: open success fd=%X\n", fd);
	set_timer_vector();
	//if(stdin_init(fileno(stdin)) < 0)
	//	printf("ledIO: stdin set non-blocking err\n");	
		
	//printf("ledIO: device open done\n");

	quit= 0;
	autoled= 1;
	Index= 0;
	b= 0;

	while(!quit) {
		if(autoled && ledtimer) {
			ledtimer= 0;
			b ^= 0x03;
			write(fd, (char *)&b, 1);
			Index++;
			sleep(2);
		}
		autoled ^= 1;
		if(Index > 10) {
			close(fd);
			ledtimer= 1;
			quit= 1;
		}

	}	// while loop
	// turn on LED
	b= 0x00;
	write(fd, (char *)&b, 1);

	return 0;
}
