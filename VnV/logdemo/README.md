## Testing the printk log levels

Check the current log level

`cat /proc/sys/kernel/printk`

You can observe the output with four indicators as follows,representing current,default,min,max log levels.

> `4    4     1     7`

Change the log level as 

`dmesg -n 6`

*or*

`echo "5" > /proc/sys/kernel/printk`

For each log level observe the behaviour when this module is loaded

You may not find any difference in `dmesg` output

In a pseudo terminal (under graphical view, in case of Desktop Linux) you may not find any difference

When you try the loading of this module in a login console (By default in case of serial console of Qemu launch), you can observe that printk output whose log level is less than the current log level will be immediately displayed to user without checking dmesg

Of course output of all log levels will be visible through `dmesg`.


