#include <linux/module.h>
#include <linux/kernel.h>
//doesn't work...
#include <sys/syscall.h">

//doesn't work cause include doesn't work....... 
extern void* sys_call_table[];

long (*orig_close)(const char* path);

int own_close(const char* path) {
    //do something
    return 0;
}

int init_module(void) {
    orig_close = sys_call_table[SYS_close];
    sys_call_table[SYS_close] = own_close;
    printk("sys_close replaced\n");
    return(0);
}

void cleanup_module(void) {
    sys_call_table[SYS_close] = orig_close;
    printk("sys_close moved back\n");
}
