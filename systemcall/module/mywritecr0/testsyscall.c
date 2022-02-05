#include <linux/module.h>
#include <linux/kallsyms.h>


#include <linux/linkage.h>
#include <linux/sys.h>
#include <linux/cache.h>
#include <linux/syscalls.h>
#include <asm/asm-offsets.h>
#include <asm/syscall.h>


//https://stackoverflow.com/questions/59851520/system-call-hooking-example-arguments-are-incorrect
//https://jm33.me/hook-system-calls-in-linux-5x.html
MODULE_LICENSE("GPL");
//typedef asmlinkage long (*custom_open) (const char __user *filename, int flags, umode_t mode);
//custom_open old_open;
typedef asmlinkage long (*sys_call_ptr_t)(const struct pt_regs *);
sys_call_ptr_t old_open;

#define _NR_new __NR_syscall_max-1
// last 435 new 435->max-1
inline void mywrite_cr0(unsigned long cr0) {
  unsigned long __forced_order;
  asm volatile("mov %0,%%cr0" : "+r"(cr0), "+m"(__forced_order));
}

void enable_write_protection(void) {
  unsigned long cr0 = read_cr0();
  set_bit(16, &cr0);
  mywrite_cr0(cr0);
}

void disable_write_protection(void) {
  unsigned long cr0 = read_cr0();
  clear_bit(16, &cr0);
  mywrite_cr0(cr0);
}

static struct {
  void **sys_call_table;
  void *orig_fn;
} tinfo;

//static asmlinkage long my_open(const char __user *filename, int flags, umode_t mode)
static asmlinkage long my_open(const struct pt_regs *regs)
{
    printk(KERN_ALERT,"hello world\n");
    /*char user_msg[256];
    pr_info("keshixing %s\n",__func__);
    memset(user_msg, 0, sizeof(user_msg));
    long copied = strncpy_from_user(user_msg, filename, sizeof(user_msg));
    user_msg[sizeof(user_msg)-1] = 0;
    pr_info("copied:%ld\n", copied);
    pr_info("%s\n",user_msg);
  //  return 0;
    return old_open(filename, flags, mode);
    */
            char __user *filename = (char *)regs->di;
            char user_filename[256] = {0};
        long copied = strncpy_from_user(user_filename, filename, sizeof(user_filename));
        if (copied > 0)
            pr_info("%s filename:%s\n",__func__, user_filename);
        return old_open(regs);
}

static int __init mod_init(void) {
  printk(KERN_INFO "Init syscall hook\n");
  tinfo.sys_call_table = (void **)kallsyms_lookup_name("sys_call_table");
  tinfo.orig_fn = tinfo.sys_call_table[__NR_open];
  old_open = tinfo.sys_call_table[__NR_open];
  disable_write_protection();
  // modify sys_call_table directly
  tinfo.sys_call_table[__NR_open] = my_open;
  enable_write_protection();
  return 0;
}

static void __exit mod_cleanup(void) {
  printk(KERN_INFO "Cleaning up syscall hook.\n");
  // backup syscall
  disable_write_protection();
  tinfo.sys_call_table[__NR_open] = tinfo.orig_fn;
  enable_write_protection();
  printk(KERN_INFO "Cleaned up syscall hook.\n");
}

module_init(mod_init);
module_exit(mod_cleanup);






