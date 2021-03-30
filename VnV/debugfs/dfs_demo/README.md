### Simple hello module

#### Build the module

`make –C <path-of-KSRC> M=$PWD modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-`

Copy generated ko file to target rootfs

```
mount –o loop,rw,sync rootfs.img /mnt/rootfs
cp hello.ko /mnt/rootfs/root
umount rootfs.img
```

#### Testing on target side

Clear kernel log buffer

`dmesg –c`

Load the module

`insmod hello.ko`

Check  kernel log buffer & list modules

`dmesg`
`lsmod`
`cat /proc/modules`

Unload the module & check log, module listing
`rmmod hello`
`dmesg`
`lsmod`

#### Testing module on host

```
file hello.ko
arm-linux-gnueabi-objdump -d hello.ko
arm-linux-gnueabi-readelf -h hello.ko
modinfo hello.ko
```

#### Explanantion/Discussion
* module_init, module_exit
* Important header files
* printk usage
* Macros

