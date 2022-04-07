/*
*   DKU Operating System Lab
*           Lab2 (Hash Queue Lock Problem)
*           Student id : 
*           Student name : 
*
*   lab1_sync_types.h :
*       - Lab2 header file.
*       - It contains Hash Queue structure, timeval functions, ... etc
*
*/

#ifndef _LAB2_HEADER_H
#define _LAB2_HEADER_H

#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <pthread.h>
#include <asm/unistd.h>

#define HASH_SIZE		13
#define LAB2_SUCCESS	0
#define LAB2_ERROR		-1

/*
 * If You need to more functions or vaiable
 * Declare functions or struct in lab2_sync_types.h
 */

/* Variable that contains number of data */
int target;

/* Strucuture for thread, hash, queue */
typedef struct threadArg {
	int node_count;
	int thread_num;
} thread_arg; // Maybe you don't need to modify this structure.

typedef struct q_node {
	struct q_node *next;
	struct q_node *prev;
	int data;
} queue_node;

queue_node *front;
queue_node *rear;

typedef struct hash_list {
	struct hash_list *next;
	struct q_node *q_loc;
} hlist_node;

hlist_node *hashlist[HASH_SIZE];

/* Lab2 Hash and Queue init functions */
void init_queue();
void init_hlist_node();

/* Lab2 Hash function */
int hash(int val);
int value_exist(int val);

/* Lab2 Hash Queue functions for single-thread */
void enqueue(queue_node *new_node);
void dequeue(queue_node *del_node);
void hash_queue_add(hlist_node *hashtable, int val);
void hash_queue_insert_by_target();
void hash_queue_delete_by_target();

/* Lab2 Hash Queue functions for Coarse-grained */
void enqueue_cg(queue_node *new_node);
void dequeue_cg(queue_node *del_node);
void hash_queue_add_cg(hlist_node *hashtable, int val);
void hash_queue_insert_by_target_cg();
void hash_queue_delete_by_target_cg();

/* Lab2 Hash Queue functions for fine-grained */
void enqueue_fg(queue_node *new_node);
void dequeue_fg(queue_node *del_node);
void hash_queue_add_fg(hlist_node *hashtable, int val);
void hash_queue_insert_by_target_fg();
void hash_queue_delete_by_target_fg();

/* Lab2_timeval.c related function */
double get_timeval(struct timeval *tv_start, struct timeval *tv_end);

#endif /* LAB2_HEADER_H*/


