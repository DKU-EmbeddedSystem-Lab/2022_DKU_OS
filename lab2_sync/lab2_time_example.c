/*
*   lab2_thread_example.c :
*       - gettimeofday usage example code.
*       
*   Implement gettimeofday code 
*/

#include <aio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#include "lab2_sync_types.h"

void loop_f() {
	int i;
	for(i = 0; i < 1000000000; i++) {
		/*Just do loop*/
	}
}

int main(int argc, char* argv[]) {
	struct timeval start, end;
	double result_T;

	gettimeofday(&start, NULL);
	
	loop_f();

	gettimeofday(&end, NULL);

	result_T = (end.tv_sec - start.tv_sec) + ((end.tv_usec - start.tv_usec)/1000000);

	printf("Loop time = %f\n", result_T);

	return 0;
}

