/*
*   lab2_thread_example.c :
*       - thread usage example code.
*       - thread argument example code.
*
*   Implement thread argument code 
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

typedef struct MultipleArg {
	int _a;
	int _b;
}MA;

void *t_func(void *multi_arg) {
	MA *my_multi_arg = (MA *)multi_arg;
	printf("a: %d, b: %d\n", my_multi_arg->_a, my_multi_arg->_b);
}

int main(int argc, char* argv[]) {
	pthread_t t1, t2;

	MA *multiple_arg;
	multiple_arg = (MA *)malloc(sizeof(MA));
	multiple_arg->_a = 10; multiple_arg->_b = 20;

	pthread_create(&t1, NULL, t_func, (void *) multiple_arg);
	pthread_create(&t2, NULL, t_func, (void *) multiple_arg);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return 0;
}

