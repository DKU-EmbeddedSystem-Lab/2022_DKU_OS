/*
*	DKU Operating System Lab
*	    Lab2 (Hash Queue Lock Problem)
*	    Student id : 
*	    Student name : 
*
*   lab2_sync_test.c :
*       - Thread-safe Hash Queue Lock Problem Test Code.
*       - Coarse-grained, fine-grained Lock Test Code.
*
*   You can compare no-lock  result, coarse grained result and fine grained result.
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

void lab2_sync_usage(char *cmd) {
	printf("\n Usage for %s : \n", cmd);
	printf("	-t: num thread, must be bigger than 0 ( e.g. 4) \n");
	printf("	-c: test target count, must be bigger than 0 ( e.g. 100000 ) \n");
	printf("	-l: determine lock types (e.g. 0=no-lock, 1=coarse-grained, 2=fine-grained) \n");
}

void lab2_sync_example(char *cmd) {
	printf("\n Example : \n");
	printf("	#sudo %s -t=4 -c=1000000 -l=0 \n", cmd);
	printf("	#sudo %s -t=16 -c=100000 -l=1 \n", cmd);
}

static void print_result(double ins_time, double del_time, double tot_time, int lock_type, int num_threads, int node_count) {
	char *cond[] = {"No-lock HQ", "Coarse-grained HQ", "Fine-grained HQ"};
	char *op[] = {"Insert", "Delete"};
	double time[] = {ins_time, del_time, tot_time};

	if (lock_type == 0) {
		for (int i = 0; i < 2; i++) {
			printf("\n=====  Multi Threads %s  %s experiment =====\n", cond[lock_type], op[i]);
			printf("\n Experiment Info \n");
			printf("	Test Node Count			: %d \n", node_count);
			printf("	Test Threads			: %d \n", num_threads);
			printf("	Execution Time			: %.2lf seconds \n", time[i]);
		}
		printf("\n	Total Execution Time		: %.2lf seconds \n", time[2]);
	} else if (lock_type == 1) {
		for (int i = 0; i < 2; i++) {
            printf("\n=====  Multi Threads %s  %s experiment =====\n", cond[lock_type], op[i]);
            printf("\n Experiment Info \n");
            printf("    Test Node Count         : %d \n", node_count);
            printf("    Test Threads            : %d \n", num_threads);
            printf("    Execution Time          : %.2lf seconds \n", time[i]);
        }
        printf("\n  Total Execution Time        : %.2lf seconds \n", time[2]);
	} else if (lock_type == 2) {
		for (int i = 0; i < 2; i++) {
		    printf("\n===== Multi Threads %s  %s experiment =====\n", cond[lock_type], op[i]);
		    printf("\n Experiment Info \n");
			printf("    Test Node Count         : %d \n", node_count);
			printf("    Test Threads            : %d \n", num_threads);
			printf("    Execution Time          : %.2lf seconds \n", time[i]);
		}
        printf("\n  Total Execution Time        : %.2lf seconds \n", time[2]);
	}
}

void* thread_job_insert(void *arg) {
	thread_arg *th_arg = (thread_arg *)arg;
    int node_c = th_arg->node_count;
	int thread_n = th_arg->thread_num;

	for(int i = 0; i < node_c/thread_n; i++) {
		target = rand() % node_c;
		hash_queue_insert_by_target();
	}
}

void* thread_job_insert_cg(void *arg) {
	thread_arg *th_arg = (thread_arg *)arg;
	int node_c = th_arg->node_count;
	int thread_n = th_arg->thread_num;

	for(int i = 0; i < node_c/thread_n; i++) {
		target = rand() % node_c;
		hash_queue_insert_by_target_cg();
	}
}

void* thread_job_insert_fg(void *arg) {
	thread_arg *th_arg = (thread_arg *)arg;
	int node_c = th_arg->node_count;
	int thread_n = th_arg->thread_num;

	for(int i = 0; i < node_c/thread_n; i++) {
		target = rand() % node_c;
		hash_queue_insert_by_target_fg();
	}
}

void* thread_job_delete(void *arg) {
	thread_arg *th_arg = (thread_arg *)arg;
    int node_c = th_arg->node_count;
	int thread_n = th_arg->thread_num;

	for(int i = 0; i < node_c/thread_n; i++) {
		target = rand() % node_c;
		hash_queue_delete_by_target();
	}
}

void* thread_job_delete_cg(void *arg) {
	thread_arg *th_arg = (thread_arg *)arg;
    int node_c = th_arg->node_count;
	int thread_n = th_arg->thread_num;

	for(int i = 0; i < node_c/thread_n; i++) {
		target = rand() % node_c;
		hash_queue_delete_by_target_cg();
	}
}

void* thread_job_delete_fg(void *arg) {
	thread_arg *th_arg = (thread_arg *)arg;
    int node_c = th_arg->node_count;
    int thread_n = th_arg->thread_num;

    for(int i = 0; i < node_c/thread_n; i++) {
        target = rand() % node_c;
        hash_queue_delete_by_target_fg();
    }
}

void hq_test(int num_threads, int node_count, int lock_type) {
	struct timeval tv_insert_s, tv_insert_e, tv_delete_s, tv_delete_e, tv_total_s, tv_total_e;
	double exe_insert, exe_delete, exe_total;
	const int num_t = num_threads;
	const int node_c = node_count;
	const int lock_t = lock_type;
	pthread_t threads[num_t];

	thread_arg *th_arg;
	th_arg = (thread_arg *)malloc(sizeof(thread_arg));

	/*
	 *  Multi Thread Insert and Delete Test No-lock
	 */
	if (lock_type == 0) {
		gettimeofday(&tv_total_s, NULL);
		printf("\n");
		
		init_hlist_node();
		init_queue();
		
		gettimeofday(&tv_insert_s, NULL);
		for(int i = 0; i < num_t; i++) {
			th_arg->node_count = node_c;
			th_arg->thread_num = num_t;

			pthread_create(&threads[i], NULL, thread_job_insert, (void *)th_arg);
		}
		
		for(int i = 0; i < num_t; i++)
			pthread_join(threads[i], NULL);
		gettimeofday(&tv_insert_e, NULL);

		gettimeofday(&tv_delete_s, NULL);
		for(int i = 0; i < num_t; i++) {
			th_arg->node_count = node_c;
			th_arg->thread_num = num_t;

			pthread_create(&threads[i], NULL, thread_job_delete, (void *)th_arg);
		}
		
		for(int i = 0; i < num_t; i++)
			pthread_join(threads[i], NULL);
		gettimeofday(&tv_delete_e, NULL);

		gettimeofday(&tv_total_e, NULL);
		exe_insert = get_timeval(&tv_insert_s, &tv_insert_e);
			
		exe_delete = get_timeval(&tv_delete_s, &tv_delete_e);
		exe_total = get_timeval(&tv_total_s, &tv_total_e);
		print_result(exe_insert, exe_delete, exe_total, lock_t, num_t, node_c);
	}
	
	/*
	 *  Multi Threads Insert and Delete Test Coarse-grained
	 */
	if (lock_type == 1) {
		gettimeofday(&tv_total_s, NULL);
		printf("\n");

		init_hlist_node();
		init_queue();
		
		gettimeofday(&tv_insert_s, NULL);
		for(int i = 0; i < num_t; i++) {
			th_arg->node_count = node_c;
			th_arg->thread_num = num_t;

			pthread_create(&threads[i], NULL, thread_job_insert_cg, (void *)th_arg);
		}

		for(int i = 0; i < num_t; i++)
			pthread_join(threads[i], NULL);
		gettimeofday(&tv_insert_e, NULL);

		gettimeofday(&tv_delete_s, NULL);
		for(int i = 0; i < num_t; i++) {
			th_arg->node_count = node_c;
			th_arg->thread_num = num_t;

			pthread_create(&threads[i], NULL, thread_job_delete_cg, (void *)th_arg);
		}

		for(int i = 0; i < num_t; i++)
			pthread_join(threads[i], NULL);
		gettimeofday(&tv_delete_e, NULL);

		gettimeofday(&tv_total_e, NULL);
		exe_insert = get_timeval(&tv_insert_s, &tv_insert_e);

        exe_delete = get_timeval(&tv_delete_s, &tv_delete_e);
        exe_total = get_timeval(&tv_total_s, &tv_total_e);
        print_result(exe_insert, exe_delete, exe_total, lock_t, num_t, node_c);
	}
	
	/*
	 *  Multi Threads Insert and Delete Test Fine-grained
	 */
	if (lock_type == 2) {
		gettimeofday(&tv_total_s, NULL);
		printf("\n");

		init_hlist_node();
		init_queue();
		
		gettimeofday(&tv_insert_s, NULL);
		for(int i = 0; i < num_t; i++) {
			th_arg->node_count = node_c;
			th_arg->thread_num = num_t;

			pthread_create(&threads[i], NULL, thread_job_insert_fg, (void *)th_arg);
		}

		for(int i = 0; i < num_t; i++)
			pthread_join(threads[i], NULL);
		gettimeofday(&tv_insert_e, NULL);

		gettimeofday(&tv_delete_s, NULL);
		for(int i = 0; i < num_t; i++) {
			th_arg->node_count = node_c;
			th_arg->thread_num = num_t;

			pthread_create(&threads[i], NULL, thread_job_delete_fg, (void *)th_arg);
		}

		for(int i = 0; i < num_t; i++)
			pthread_join(threads[i], NULL);
		gettimeofday(&tv_delete_e, NULL);

		gettimeofday(&tv_total_e, NULL);
		exe_insert = get_timeval(&tv_insert_s, &tv_insert_e);

        exe_delete = get_timeval(&tv_delete_s, &tv_delete_e);
        exe_total = get_timeval(&tv_total_s, &tv_total_e);
        print_result(exe_insert, exe_delete, exe_total, lock_t, num_t, node_c);
	}

	printf("\n");
}

int main(int argc, char *argv[]) {
	int n; char junk;
	int num_threads = 0, node_count = 0, lock_type = 0;
	
	for (int i = 1; i < argc; i++) {
		if (sscanf(argv[i], "-t=%d%c", &n, &junk) == 1) {
			num_threads = n;
		}
		else if (sscanf(argv[i], "-c=%d%c", &n, &junk) == 1) {
			node_count = n;
		}
		else if (sscanf(argv[i], "-l=%d%c", &n, &junk) == 1) {
			lock_type = n;
		} else goto INVALID_ARGS;
	}
	if((num_threads > 0) && (node_count > 0)) {
		hq_test(num_threads, node_count, lock_type);
	} else goto INVALID_ARGS;
	
	return LAB2_SUCCESS;

INVALID_ARGS:
	lab2_sync_usage(argv[0]);
	lab2_sync_example(argv[0]);

	return LAB2_ERROR;
}

