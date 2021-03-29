obj-m += thdemo.o

KSRC=/lib/modules/$(shell uname -r)/build
#KSRC=/home/rsola/eworkdir/buildws/linux-4.14.177
#ARCH=arm
#CROSS_COMPILE_PREFIX=arm-linux-gnueabi-

all:
	make -C ${KSRC} M=${PWD} modules #ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} clean  #ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-

