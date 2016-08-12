
#WARN    := -W -Wall -Wstrict-prototypes 
WARN    := -W  
PATH_C=/usr/bin

INCLUDE := -isystem /usr/src/linux/include
#FLAG := -fomit-frame-pointer -fno-strict-aliasing -G0 -mno-abicalls -fno-pic -mips2 -Wa,--trap -pipe -mlong-calls -DEXPORT_SYMTAB

CFLAGS  := -O2  ${WARN} ${INCLUDE}
CC      := ${PATH_C}/gcc
OBJS    := ${patsubst %.c,%.o,${wildcard *.c}}

all: ${OBJS}
	$(CC) ite8712-ledio-ap.c key.c  -o ledio-ap

.PHONY: clean

clean:
	rm -fr *.o
	rm -fr *~



