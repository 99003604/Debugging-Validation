#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>

static struct task_struct *task1;
static struct task_struct *task2;

int count=50;
module_param(count,int,S_IRUGO);

wait_queue_head_t w1;

static int val=100;
static int buflen=0;

static int thread_one(void *pargs)
{
    int i;
    wait_event_interruptible(w1, (buflen > 0) );
    for(i=1;i<=count;i++)
    {
        printk("Consumer--%d\n",i);
        val++;
    }
	return 0;
}

static int thread_two(void *pargs)
{
    int i;
    for(i=1;i<=count;i++)
    {
        printk("Producer--%d\n",i);
        val--;
    }
    buflen++;
    wake_up_interruptible(&w1);
	return 0;
}

static int __init wqdemo_init(void) {        //init_module
  init_waitqueue_head(&w1);
  task1=kthread_run(thread_one, NULL, "thread_A");  //kthread_create + wake_up_process
  task2=kthread_run(thread_two, NULL, "thread_B");
  printk("Thread Demo..welcome\n");
  return 0;
}
static void __exit wqdemo_exit(void) {       //cleanup_module
  /*if(task1)
      kthread_stop(task1);
  if(task2)
      kthread_stop(task2);*/
  printk("Thread Demo,Leaving the world,val=%d\n",val);
}

module_init(wqdemo_init);
module_exit(wqdemo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajesh Sola");
MODULE_DESCRIPTION("Thread Example Module");
