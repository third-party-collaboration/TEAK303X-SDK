/* This is a gpio testing code. */
/* 1. Create a gpio device in /dev directory with major 95 */
/*      #mknod /dev/powerio c 98 0 
	2. Operation
		# r -- Read GPIO function
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
	unsigned char c, b;
	int  datafound;
	int ret, i;
	int quit;
	unsigned char val;
	unsigned int set;
	static int status= 0;
	unsigned char buf[80];
	//u32		val[2];
	unsigned char *p=buf;
	//int TxSize;
	int fd;
	u16 TimeOut_Counter=0;
	
    printf("powerIO: Start POWER IO Application \n");
 
	fd= open("/dev/powerio", O_RDWR);
	// Start the Net
	if(fd < 0) {
		printf("powerIO:  Can not open device driver\n");
		exit(0);	
	}
	printf("powerIO: open success fd=%X\n", fd);
	//set_timer_vector();
	if(stdin_init(fileno(stdin)) < 0)
		printf("powerIO: stdin set non-blocking err\n");	
		
	printf("powerIO: device open done\n");

	quit= 0;
	datafound= 0;
	status= 0x01;
	c= b= 0;
	val= 0;

	while(!quit) {
        c= 0;

		ret=stdin_read((char *)&c, fileno(stdin));
		//printf("ret=%d C=%X\n", ret, c);
		if( c == 0x0A) 
		    continue;
		
		if(ret > 0) {
			switch(c) {
				case '?':
					printf("Power IO operation command\n");
					printf(" r -- Read Power IO function\n");
					printf(" ? -- help\n");
					printf(" q -- Quit program\n");
					break;
				case 'q':
					quit= 1;
					if(status & 0x01) {
						close(fd);
						status= 0x02;
					}
					break;
      			case 0x0A:      // return code
					break;
				case 'r':   // Get gpio input value
					ret=read(fd, (char *)&b, 1);
					if(ret > 0)
						printf("hex val= 0x%02X\n", b);
					else 
						printf("read err %d\n", ret);
					break;
				default:
					printf("powerIO-ap: command err !\n");
				    break;

			}
		}
		ret=read(fd, (char *)&b, 1);
		if(ret > 0) {
			if( b==0)
				printf("button pressed -- hex= 0x%02X\n", b);
		}
	}	// while loop
	return 0;
}
