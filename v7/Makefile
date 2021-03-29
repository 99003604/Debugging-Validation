obj-m += pschar.o

KSRC= /home/mytsp00472-ubuntu/LTTS/BasicDeviceDrivers/ebuildws/packages/linux-4.14.224


all:
	make -C ${KSRC} M=${PWD} modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
clean:
	make -C ${KSRC} M=${PWD} clean ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
