#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h> 

asmlinkage long get_nice_inc(pid_t pid){
    struct task_struct* ts = find_task_by_vpid(pid);

    return ts->nice_inc;
}