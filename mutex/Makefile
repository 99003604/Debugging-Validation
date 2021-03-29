obj-m += mutexdemo.o

KSRC=/lib/modules/$(shell uname -r)/build
#ARCH=arm
#CROSS_COMPILE_PREFIX=arm-linux-gnueabi-

all:
	make -C ${KSRC} M=${PWD} modules
clean:
	make -C ${KSRC} M=${PWD} clean

