obj-m += bypass.o

all: ${OBJS}
	make -C /lib/modules/2.6.18/build M=$(PWD) modules

clean:
	make -C /lib/modules/2.6.18/build M=$(PWD) clean
	
