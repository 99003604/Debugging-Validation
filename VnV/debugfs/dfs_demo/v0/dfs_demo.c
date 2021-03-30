//Ref:- https://www.kernel.org/doc/Documentation/filesystems/debugfs.txt
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/fs.h>


#define MAX_SIZE 64

struct dentry *pdir;
struct dentry *pfile;
int fileValue; 
int len=MAX_SIZE;
char pbuffer[MAX_SIZE];

static ssize_t myreader(struct file *fp, char __user *user_buffer, 
                                size_t count, loff_t *position) 
{ 
     return simple_read_from_buffer(user_buffer, count, position, pbuffer, len);
} 
 
/* write file operation */
static ssize_t mywriter(struct file *fp, const char __user *user_buffer, 
                                size_t count, loff_t *position) 
{ 
        if(count > len ) 
                return -EINVAL; 
  
        return simple_write_to_buffer(pbuffer, len, position, user_buffer, count); 
} 

static const struct file_operations fops_debug = { 
  .read = myreader, 
  .write = mywriter, 
}; 
 

static int __init dfs_demo_init(void) {        //init_module
  pdir=debugfs_create_dir("psample", NULL);
  pfile=debugfs_create_file("status",0644,pdir, &fileValue, &fops_debug);
  printk("Hello World..welcome\n");
  return 0;
}
static void __exit dfs_demo_exit(void) {       //cleanup_module
  debugfs_remove(pfile);
  debugfs_remove(pdir);
  //debugfs_remove_recursive(pdir); 
  printk("Bye,Leaving the world\n");
}
module_init(dfs_demo_init);
module_exit(dfs_demo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your name");
MODULE_DESCRIPTION("A Hello, World Module");
