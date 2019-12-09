#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <assert.h>

typedef struct worker
{
	void *(*process)(void *arg);
	void *arg;
	struct worker *next;
}CThread_worker;

typedef struct 
{
	pthread_mutex_t queue_lock;
	pthread_cond_t  queue_ready;

	CThread_worker *queue_head;

	int shutdown;
	pthread_t *threadid;

	int max_thread_num;
	int cur_queue_size;
}CThread_pool;

int pool_add_worker(void* (*process)(void *arg), void *arg);
void *thread_routine(void *arg);

static CThread_pool *pool = NULL;

void pool_init(int max_thread_num)
{
	pool  = (CThread_pool *)malloc(sizeof(CThread_pool));

	pthread_mutex_init(&(pool->queue_lock), NULL);
	pthread_cond_init(&(pool->queue_ready), NULL);

	pool->queue_head = NULL;
	pool->max_thread_num = max_thread_num;
	pool->cur_queue_size = 0;

	pool->threadid = (pthread_t *)malloc(max_thread_num * sizeof (pthread_t));

	int i = 0;
	for(i = 0; i < max_thread_num; i++)
		pthread_create(&(pool->threadid[i]), NULL, thread_routine, NULL);			
}

int pool_add_worker(void* (*process)(void *arg), void *arg)
{
	CThread_worker *newworker = (CThread_worker*)malloc(sizeof(CThread_worker));

	newworker->process = process;
	newworker->arg     = arg;
	newworker->next    = NULL;

	pthread_mutex_lock(&(pool->queue_lock));

	CThread_worker *member = pool->queue_head;
	if(member != NULL)
	{
		while(member->next != NULL)
			member = member->next;
		member->next = newworker;
	}
	else
		pool->queue_head  = newworker;

	pool->cur_queue_size++;
	pthread_mutex_unlock(&(pool->queue_lock));

	pthread_cond_signal(&(pool->queue_ready));

	return 0;
}


int pool_destroy()
{
	if(pool->shutdown)
		return -1;
}


void *thread_routine(void *arg)
{
	printf("start thread 0x%x\n", pthread_self());

	while(1)
	{
		pthread_mutex_lock(&(pool->queue_lock));
		while(pool->cur_queue_size == 0 && !pool->shutdown)
		{
			printf("thread 0x%x is waiting\n", pthread_self());
			pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));

		}

		pool->cur_queue_size --;
		CThread_worker *worker = pool->queue_head;
		pool->queue_head = worker->next;
		pthread_mutex_unlock(&(pool->queue_lock));

		(*(worker->process))(worker->arg);

		free(worker);
		worker = NULL;

	}
	pthread_exit(NULL);
}


void *myprocess(void *arg)
{
	printf ("threadid is 0x%x, working on task %d\n", pthread_self(),*(int *)arg);  
    sleep (1);
    return NULL;  
}

int main()
{
	pool_init(3);

	int *worknum = (int *)malloc(4*10);
	int i;
	for(i = 0; i < 10; i++)
	{
		worknum[i] = i;
		pool_add_worker(myprocess, &worknum[i]);
	}

	sleep(5);
	free(worknum);

	return 0;
}
















































