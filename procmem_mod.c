#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>

static int pid = 1;

struct proc_segs {
	unsigned long studentID;
	unsigned long start_code;
	unsigned long end_code;
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_heap;
	unsigned long end_heap;
	unsigned long start_stack;

};

static long sys_procmem(int pid, struct proc_segs *info) {
	struct task_struct *t;

	for_each_process(t){
		if(t->pid == pid) {
			printk(KERN_INFO "PID: %d\n", t->pid);
			if(t->mm != NULL) {
				printk(KERN_INFO "p->mm not null\n");
				info->studentID = 1752054;
				info->start_code = t->mm->start_code;
				info->end_code = t->mm->end_code;
				info->start_data = t->mm->start_data;
				info->end_data = t->mm->end_data;
				info->start_heap = t->mm->start_brk;
				info->end_heap = t->mm->brk;
				info->start_stack = t->mm->start_stack;
				return 0;
			}
		}
	}

	return -1;
}

static int __init procmem_init(void) {
	struct proc_segs info;
	long rv;
	printk(KERN_INFO "Starting kernel module!\n");
	rv = sys_procmem(pid, &info);
	if(rv == 0)
		printk(KERN_INFO "student ID: %lu\ncode segment: 0%lx - 0%lx\ndata segment: 0%lx - 0%lx\nheap segment: 0%lx - 0%lx\nstack segment: 0%lx\n", info.studentID, info.start_code, info.end_code, info.start_data, info.end_data, info.start_heap, info.end_heap, info.start_stack);
	else
		printk(KERN_INFO "Not found\n");

	return 0;
}

static void __exit procmem_cleanup(void) {
	printk(KERN_INFO "Cleaning up module\n");
}

module_init(procmem_init);
module_exit(procmem_cleanup);
