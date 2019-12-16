/****
int sem_init(sem_t *sem, int pshared, unsigned int value);
初始化信号量；pshared=0，表示局部的，用于线程间的；
            pshared=1，表示多进程间共享的；

sem_wait：将信号量的值减1；
sem_post：将信号量的值加1；


******/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>


sem_t sem;

void *fun_one(void *arg)
{
	int *p = (int *)arg;
	sem_wait(&sem);

	printf("thead 1 running :");
	printf("[%d].....\n", *p);
}

void *fun_two(void *arg)
{
	int *p = (int *)arg;
	printf("thead 2 2 2 2 running ....\n");
	*p = *p + 1;
	sem_post(&sem);
}

int main()
{
	sem_init(&sem, 0, 0);
	pthread_t thread_id[2];

	int a = 0;
	printf("main thread is running.....\n");

	pthread_create(&thread_id[0], NULL, fun_one, (void*)&a);

	sleep(10);

	pthread_create(&thread_id[1], NULL, fun_two, (void*)&a);

	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);

	sem_destroy(&sem);

	return 0;
}




























