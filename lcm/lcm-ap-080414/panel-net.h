/* define command constant used in the hmio-10-main.c */

#define 	CONNECT 		0x05
#define	DISCONNECT	0x06
#define	ALARM			0x07
#define	WRITE			0x08
#define 	PRINT1			0x09
#define	PRINT2			0x0A
//#define 	CHECK       0x0A
#define 	ACK		    	0x0B
#define 	NACK			0x0C
#define 	CONFIRM		0x0D
#define 	RESET			0x0E

#define 	FRAME_MASK	0xFF
#define 	TIMEOUT		2
#define 	ESC         	0x1B

/* Data Frame Definition 
   Header  command  length  Data  CRC-Checksum   Tail
    FF      WRITE    2 bytes  n     2 bytes       FF
	HCM-200 to Panel
			  ID      [1:99]
			  CD      [1:99]
			  SWITCH  [1:8]    1:2(ON/OFF)     
			
    Panel to HCM-200
			  ID      [1:99]
			  SWITCH  [1:2]    1:2 (ON/OFF)
			  RDS     [1:2]
*/

#define				MAX_SIZE		22
#define				TXFRAME_SIZE	22

static char		 	Mode=0;		// 0:IDLE, 1:command
static char    		dataframe[MAX_SIZE];
static char	   		txframe[TXFRAME_SIZE];
