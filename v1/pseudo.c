#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>


dev_t pdevid;
int ndevices=1;

static int __init pseudo_init(void)
{
    int ret;
    ret=alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
    if(ret)
    {
        printk("Pseudo: Failed to register driver\n");
        return -EINVAL;
    }
    printk("Successfully registered,major=%d,minor=%d\n", MAJOR(pdevid), MINOR(pdevid));
    printk("Pseudo Driver Sample..welcome\n");
    return 0;
}

static void __exit pseudo_exit(void)
{
    unregister_chrdev_region(pdevid, ndevices);
    printk("Pseudo Driver Sample..Bye\n");
}

module_init(pseudo_init);
module_exit(pseudo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Bablu Kavali");
MODULE_DESCRIPTION("A Simple Module");