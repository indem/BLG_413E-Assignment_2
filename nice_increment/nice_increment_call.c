#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h> 

asmlinkage long set_nice_inc(pid_t pid, int value){
    struct task_struct* ts = find_task_by_vpid(pid);
    ts->nice_inc = value;

    return ts->nice_inc;
}