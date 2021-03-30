#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>

static void timer_handler(struct timer_list *tlist);

//static DEFINE_TIMER(timer, timer_handler);
struct timer_list timer;

u64 prev,cur;
int *ptr=NULL;

static void timer_handler(struct timer_list *tlist)
{
    cur=jiffies;
    printk("timer:jiffies=%llu, diff=%u\n",cur,jiffies_to_msecs(cur-prev));
    prev=cur;
    //*ptr=100;
    BUG_ON(5=5);
    mod_timer(&timer, cur + 1000 );
}

static int __init timerdemo_init(void) { 
    prev=cur=jiffies;
    printk("init:jiffies=%lu\n",jiffies); 
    timer_setup(&timer, timer_handler, 0);      
    mod_timer(&timer, cur + 1000);
    printk("Timer Demo..welcome\n");
    return 0;
}
static void __exit timerdemo_exit(void) {       
  del_timer_sync(&timer);
  printk("Timer Demo,Leaving the world\n");
}

module_init(timerdemo_init);
module_exit(timerdemo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajesh Sola");
MODULE_DESCRIPTION("Timer Example Module");
