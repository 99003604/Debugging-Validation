/** 
* Implement read, write operations using kernel buffer
*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/kfifo.h>

dev_t pdevid;
struct cdev cdev;
int ndevices=1;
module_param(ndevices,int,S_IRUGO);

struct class *pclass;
struct device *pdev;

unsigned char *pbuffer;
#define MAX_SIZE 256

struct kfifo myfifo;

int pseudo_open(struct inode* inode , struct file* file)
{
   //dump_stack();
   printk("Pseudo--open method\n");
   return 0;
}
int pseudo_close(struct inode* inode , struct file* file)
{
   //dump_stack();
   printk("Pseudo--release method\n");
   return 0;
}
ssize_t pseudo_read(struct file * file, char __user * ubuf , size_t size, loff_t * off)
{
   int ret;
   int rcount, klen;
   char* tbuf=NULL;

   //dump_stack();
   printk("Pseudo--read method\n");

  
   if(kfifo_is_empty(&myfifo))        
   {
        printk("buffer is empty\n");
        return 0;
   }

   rcount = size;
   klen = kfifo_len(&myfifo);
   if(rcount > klen)      
      rcount = klen;            //min of kfifo len, size
   //may print kfifo_len, rcount, size

  // tbuf = kmalloc(rcount, GFP_KERNEL);        //char tbuf[rcount]
   
   *tbuf=500;
   kfifo_out(&myfifo, tbuf, rcount);
   ret=copy_to_user(ubuf, tbuf, rcount);
   if(ret)
   {
      printk("copy from user failed\n");
      return -EFAULT;
   }
   kfree(tbuf);

   printk("read operation success\n"); //may print kfifo_len, rcount, size
   return rcount;
}
ssize_t pseudo_write(struct file * file, const char __user * ubuf , size_t size, loff_t * off)
{
   int ret;
   int kremain, wcount;
   char* tbuf=NULL;
   //dump_stack();
   printk("Pseudo--write method\n");

   if(kfifo_is_full(&myfifo))       //kfifo_avail(&myfifo)==0
   {
      printk("buffer is full, no space to write\n");
      return -ENOSPC;       
   }

   wcount = size;
   kremain = kfifo_avail(&myfifo);
   if(kremain < size)
      wcount =  kremain ;       //min of size, kremain
   //may print kfifo_avail, wcount, size

   //tbuf = kmalloc(wcount, GFP_KERNEL);        //char tbuf[wcount];
   //*tbuf=100;
   memcpy(tbuf, "abcdxyz", 7);
   ret=copy_from_user(tbuf, ubuf, wcount);
   if(ret) 
   {
      printk("copy from user failed\n");
      return -EFAULT;
   }
   kfifo_in(&myfifo, tbuf, wcount);
   //kfree(tbuf);

   printk("successfully written the content"); //may print kfifo_avail, wcount, size
   return wcount; 
}

struct file_operations fops =  {
  .open    = pseudo_open,
  .release = pseudo_close,
  .write   = pseudo_write,
  .read    = pseudo_read
};  //where is the definition?

static int __init psuedo_init(void) 
{       
  int ret,i=0;
  pclass = class_create(THIS_MODULE, "pseudo_class");
  BUG_ON(ndevices>5);
  ret=alloc_chrdev_region(&pdevid, 0, ndevices, "pseudo_sample");
  if(ret) 
  {
     printk("Pseudo: Failed to register driver\n");
     return -EINVAL;
  }
  pbuffer = kmalloc(MAX_SIZE, GFP_KERNEL);
  if(pbuffer == NULL) 
  {
     printk("Pseudo : kmalloc failed\n");
     return -ENOMEM;             //goto end
  }
  kfifo_init(&myfifo, pbuffer, MAX_SIZE);
  //kfifo_alloc(&myfifo, MAX_SIZE, GFP_KERNEL);

  cdev_init(&cdev, &fops);
  kobject_set_name(&cdev.kobj,"pdevice%d",i);
  ret = cdev_add(&cdev, pdevid, 1);

  pdev = device_create(pclass, NULL, pdevid, NULL, "psample");
  if(pdev==NULL) 
  {
    printk("error in creating device file\n");
    return 0;
  }

  printk("Successfully register,major=%d,minor=%d\n",
                                    MAJOR(pdevid), MINOR(pdevid));
  printk("Pseudo Driver Sample..welcome\n");
  return 0;
}
static void __exit psuedo_exit(void) 
{ 
  kfifo_free(&myfifo);      
  cdev_del(&cdev);
  device_destroy(pclass, pdevid);

  unregister_chrdev_region(pdevid, ndevices);
  class_destroy(pclass);
  printk("Pseudo Driver Sample..Bye\n");
}

module_init(psuedo_init);
module_exit(psuedo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("A Hello, World Module");
