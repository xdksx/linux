#include<linux/init.h>
#include<linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");//GPL
static int hello_init(void)//模块初始化函数
{
   printk(KERN_ALERT "hello,world\n");//内核的printf
   return 0;
}
static void hello_exit(void)//模块清理退出函数
{
 printk(KERN_ALERT "goodbye,world,ksance\n");
 }
int mudule_init(hello_init);//insmod时运行
module_exit(hello_exit);//rmsomd时运行
