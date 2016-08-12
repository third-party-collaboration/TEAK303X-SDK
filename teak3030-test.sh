#!/bin/sh
#
#
#
# Insert device driver module
insmod /root/e1000e.ko
insmod /root/bypass.ko
insmod /root/ite8712-ledio.ko
insmod /root/ite8712-watchdog.ko

QUIT="N"
while test $QUIT != Q ;
do
echo "Teak303x series Testing, please enter the char to select the function\n"
echo "B. bypass"
echo "L. LED Status"
echo "W. Watchdog"
echo "Q. quit"
echo "enter (B, L, W, Q)"
read select_func
# echo "cmd: $select_func"
case $select_func in
	B) echo "Bypass Test"
	/root/bypass-ap
	;;
	W) echo "Watchdog Test"
	/root/wathdog-ap
	;;
	L) echo "LED Status"
	/root/ledio-ap
	;;
	Q) echo "Quit"
	QUIT="Q"
	;;
	*) echo "Bad command";;
esac
done

