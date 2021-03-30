obj-m += oops-demo-1.o oops-demo-simple.o timerdemo.o

KSRC = /home/ltts/eworkspace/kernal_ws/linux-4.14.224
ARCH=arm
CROSS_COMPILE_PREFIX=arm-linux-gnueabi-
EXTRA_CFLAGS += -g

all:
	make -C ${KSRC} M=${PWD} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE_PREFIX} modules
clean:
	make -C ${KSRC} M=${PWD} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE_PREFIX} clean
