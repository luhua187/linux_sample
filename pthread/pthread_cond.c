#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cond  = PTHREAD_COND_INITIALIZER;

void *thread1(void *);
void *thread2(void *);

int i = 1;

int main()
{
	pthread_t t_a;
	pthread_t t_b;

	pthread_create(&t_a, NULL, thread2, NULL);
	pthread_create(&t_b, NULL, thread1, NULL);

	pthread_join(t_b, NULL);

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	exit(0);

}


void *thread1()
{
	for(i = 1; i <= 9; i++)
	{
		pthread_mutex_lock(&mutex);
		printf("call  thread1 \n");
		if(i % 3 == 0)
			pthread_cond_signal(&cond);
		else
			printf("thread1: %d \n",i);

		pthread_mutex_unlock(&mutex);

		sleep(1);
	}
}

void *thread2()
{
	while(i < 9)
	{
		pthread_mutex_lock(&mutex);
		printf("call threa2\n");
		if(i % 3 != 0)
			pthread_cond_wait(&cond, &mutex);
		printf("thread2: %d\n", i);

		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

































