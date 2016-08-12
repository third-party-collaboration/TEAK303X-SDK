obj-m += ite8712-ledio.o

all: ${OBJS}
	make -C /tftpboot/oak2030/lib/modules/2.6.18/build M=$(PWD) modules

clean:
	make -C /tftpboot/oak2030/lib/modules/2.6.18/build M=$(PWD) clean
	
