#include <procmem.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

int main() {
	pid_t mypid = getpid();
	printf("PID: %d\n", mypid);
	struct proc_segs info;

	if(procmem(mypid, &info) == 0) {
		printf("My student ID: %lu\n", info.studentID);
		printf("Code segment: 0%lx - 0%lx \n", info.start_code, info.end_code);
		printf("Data segment: 0%lx - 0%lx \n", info.start_data, info.end_data);
		printf("Heap segment: 0%lx - 0%lx \n", info.start_heap, info.end_heap);
		printf("Start stack: 0%lx\n", info.start_stack);
	} else 
		printf("Cannot get the information from the process %d\n", mypid);

	sleep(100);

	return 0;
}
