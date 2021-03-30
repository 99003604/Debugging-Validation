obj-m += logdemo.o

KSRC=/home/ltts/eworkspace/kernal_ws/linux-4.14.224
ARCH=arm
CROSS_COMPILE_PREFIX=arm-linux-gnueabi-

all:
	make -C ${KSRC} M=${PWD} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE_PREFIX} modules
clean:
	make -C ${KSRC} M=${PWD} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE_PREFIX} clean

