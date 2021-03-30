//#include <linux/init.h>
//#include <linux/module.h>
//#include <linux/kernel.h>
#include <stdio.h>
int *ptr=NULL;
int choice=1;

void do_write(void) {
    int i,dummy=0;
    for(i=1;i<=10;i++)              //dummy code
      dummy+=i;
    *ptr = 100;                     //suspected code
    printf("end of do_write\n");
}
void do_read(void) {
    int val,i,dummy;
    for(i=1;i<=10;i++)              //dummy code
      dummy+=i;
    val = *ptr;                     //suspected code
    printf("val is %d\n",*ptr);
}
   
int main(int argc,char* argv[])
{
     //init_module
  printf("Hello World..welcome\n");
//  int choice=strtoul(argv[1], NULL,10);
  if(choice==1)
     do_write();   
  else
     do_read();
  return 0;
}
