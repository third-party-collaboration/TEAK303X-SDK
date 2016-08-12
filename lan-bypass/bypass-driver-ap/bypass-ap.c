/* This is a bypass demo AP */
/* This code is used to test the ByPASS function implemented in the board 5010 for ARinfotek */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>				
#include <sys/types.h>			
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>	
#include <sys/ioctl.h>
#include <termios.h>
typedef	unsigned int 		u32;
typedef	unsigned short		u16;
typedef unsigned char		u8;

u16 bypass_timer= 0;
u16 bypass_ctrl= 0;
int fd;


/******************************************************************
* Prototype
******************************************************************/

/* The following three statements are defined in key.c */
extern int stdin_init(int);
extern int stdin_read(char *c, int fd);
void set_timer_vector(void);

inline void wr_bypass(u16 set)
{
	write(fd, &set, sizeof(unsigned short));
}

int rd_bypass(u16 *buf)
{
	return read(fd, buf, sizeof(unsigned short));
}
inline void enable_bypass_immediately(void)
{
	bypass_ctrl &= 0x00E7;		// clear
	bypass_ctrl |= 0x14;
	wr_bypass(bypass_ctrl);	
}

inline void bypass_back2Normal(void)
{
	bypass_ctrl &= 0x00E7;
	bypass_ctrl |= 0x0C;
	wr_bypass(bypass_ctrl);	
}

inline void bypass_timerCtrl(void)
{
	bypass_ctrl &= 0x00E7;
	bypass_ctrl |= 0x1C;		// timer control in controller reg
	bypass_ctrl |= bypass_timer;
	wr_bypass(bypass_ctrl);	
}

inline void bypass_timerSetting(u8 tcode)
{
	bypass_timer &= 0x00F0;
	bypass_timer |= 0x40 | tcode;		// timer setting
	bypass_timer <<= 8;
	//bypass_timer |= bypass_ctrl;		// combine two registers
	printf("bypass timer+ctrl=0x%X\n", bypass_timer);
	//wr_bypass(bypass_timer);	
}
inline void bypass_disable_timer(void)
{
	bypass_timer &= 0xBF;
	bypass_timer <<= 8;
	wr_bypass(bypass_timer);	
}
inline void check_timer_status(void)
{
	u16 timeout;
	int ret;

	timeout= 0x00;
	ret=rd_bypass(&timeout);
	if(ret) {
		if(timeout & 0x01)
			printf("Timer is TimeOut\n");
		else
			printf("Timer is counting\n");
	}
	else
		printf("read error\n");
}

inline void normal_poweroff(void)
{
	bypass_ctrl &= 0xFC;
	wr_bypass(bypass_ctrl);	

}

inline void bypass_poweroff(void)
{
	bypass_ctrl &= 0xFC;
	bypass_ctrl |= 0x01;	// bypass when power off
	wr_bypass(bypass_ctrl);	
}

inline void bypass_keep_preState(void)
{
	bypass_ctrl &= 0xFC;
	bypass_ctrl |= 0x02;	// bypass keep pre_state when power off
	wr_bypass(bypass_ctrl);	
}
void check_bypass_status(void)
{
	u16 bypass_mode;
	int ret;

	bypass_mode= 0x10;
	ret=rd_bypass(&bypass_mode);
	if(ret) {
		if(bypass_mode & 0x01)
			printf("Current state is BYPASS\n");
		else
			printf("Current state is NORMAL\n");
	}
	else
	 	printf("check bypass status -- read error\n");
}

inline void disable_bypass(void)
{
	bypass_ctrl &= 0xFB;
	wr_bypass(bypass_ctrl);
}




char Version[]= "V1.10";

/* Start the interrupt-driven serial I/O */
main(int argc, char *argv[]){
	unsigned char c, b;
	int  ret;
	int	  set;
	int quit;
	int size;
	static int status= 0;
	u8 tcode=0;
	
	
    printf("bypass-ap: Start LAN bypass-AP \n");

	fd= open("/dev/bypass", O_RDWR);
	// Start the Net
	if(fd < 0) {
		printf("bypass-ap:  Can not open device driver\n");
		exit(0);	
	}
	printf("bypass-ap: open success fd=%X\n", fd);

//	if(stdin_init(fileno(stdin)) < 0)
//		printf("bypass-ap: stdin set non-blocking err\n");	
		
	printf("bypass-ap: LAN bypass AP\n");

	quit= 0;

//	datafound= 0;
	status= 0x01;
	c= 0;

	
	while(!quit) {
        c= 0;
		ret=stdin_read((char *)&c, fileno(stdin));

		if( c == 0x0A) 
		    continue;
		
		if(ret > 0) {
			switch(c) {
				case '?':
					printf("3020-bypass operation command\n");
					printf("B - bypass back to normal\n");
					printf("C - Check bypass status\n");
					printf("D - Disable bypass\n");
					printf("E - enable bypass immediately\n");
					printf("N - Normal when power off\n");
					printf("A - Activate bypass when power off\n");
					printf("K - Keep bypass pre-state when power off\n");
					printf("t - disable bypass timer\n");
					printf("c - check timeout status\n");
					printf("T - byass contolled by timer\n");
					printf("q - quit\n");
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
				case 'B':		// bypass back to normal
					bypass_back2Normal();
					break;
				case 'C':		// Check bypass status
					check_bypass_status();
					break;
				case 'D':	// disable bypass
					disable_bypass();
					break;
				case 'E':	// enable bypass immediately
					enable_bypass_immediately();
					break;
				case 'N':	// Normal when power off
					normal_poweroff();
					break;
				case 'A':
					bypass_poweroff();
					break;
				case 'K':
					bypass_keep_preState();   // keep pre_state when power off
					break;
				case 't':	// disable bypass timer
					bypass_disable_timer();
					break;
				case 'c':	// check timeout status
					check_timer_status();
					break;
				case 'T':
					printf("Please timer setting value(hex): ");
					scanf("%x", &tcode);
					bypass_timerSetting(tcode);		// 4 sec.
					bypass_timerCtrl();
					break;
				default:
					printf("3020: bypass command err !\n");
				    break;
			} // switch
		}  // if

	}	// while loop
	return 0;
}
