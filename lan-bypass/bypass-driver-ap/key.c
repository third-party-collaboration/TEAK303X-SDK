/******************************************************************
* MACRO's  
******************************************************************/

//#define DEVICE              "/dev/ttyUSB1"  // open()
//#define FLAGS               O_RDWR  			// read + write 

/* Header files required for this AP
******************************************************************/
#include <stdio.h>
#include <errno.h>				// errno
#include <sys/types.h>				// open()
#include <sys/stat.h>				// open()
#include <fcntl.h>				// open()
#include <unistd.h>				// read() + write()
#include <sys/ioctl.h>				// io_ctl();
#include <signal.h>
#include <string.h>
#include <sys/time.h>

/******************************************************************
* Global variables
******************************************************************/
//int fd;					// for open
//FILE *fp;

void timer_handler(int signum)
{
	static int count= 0;
//	printf("key: timer expired %d times\n", ++count);

	if(++count >= 1) {
		count= 0;
	}
}

void set_timer_vector(void)
{
	struct sigaction sa;
	struct itimerval timer;

	/* Install timer_handler as the signal handler for SIGVTALRM */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler= &timer_handler;
	sigaction(SIGVTALRM, &sa, NULL);

	/* Configure the timer to expire after 150 msec ...*/
	timer.it_value.tv_sec= 0;
	timer.it_value.tv_usec= 150000;
	/* ... and every 250 msec after that ..*/
	timer.it_interval.tv_sec= 0;
	timer.it_interval.tv_usec= 150000;
	/* Start a virtual timer.  It counts down whenver this process is executing. */

	setitimer(ITIMER_VIRTUAL, &timer, NULL);
}
int stdin_init(int fd) 
{
	/* set file to non-blocking */
	int flags= fcntl(fd, F_GETFL, 0);
	if(fcntl(fd, F_SETFL, flags | O_NONBLOCK))
		return -1;
	set_timer_vector();
	return 0;
}

stdin_read(char *c, int fd)
{
	return read(fd, c, 1);
}

#if 0
main(void)
{
   unsigned char buffer[128];
	char c;
	int  ret;
        
#if 0
   if((fd = open(fd, FLAGS)) <0) {
		printf("key: open failure\n");
     	return FALSE;
	}
           
	if(fcntl(fp, F_SETFL, O_NONBLOCK) < 0){
		printf("key: set non-blocking err\n");
		return 0;
	}
#endif
	printf("key: Non-Blocking testing \n");

	set_timer_vector();
	if(stdin_init(fileno(stdin)) < 0)
		printf("key: set non-blocking err\n");

 
	while (1) {
		ret=stdin_read(&c, fileno(stdin));
		if( c == 0x0A)
		    continue;
		if(ret > 0)
			printf("%X \n", c);
		if(c == 'q')
			break;
	}// end while
	//fclose(fp);
	return 0;
        
}
#endif



