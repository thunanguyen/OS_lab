#include "procmem.h"
#include <linux/kernel.h>
#include <sys/syscall.h>

#define _SYS_PROCMEM 377

long procmem(int pid, struct proc_segs *info) {
	long result;
	result = syscall(_SYS_PROCMEM, pid, info);

	return result;
}
