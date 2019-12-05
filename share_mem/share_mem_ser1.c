#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#define PRI_SHM_ID 1024
#define PATH_SHM "home/lu/"

int main()
{
	key_t key_v = 0;
	char *p = NULL;
	int nshmid = 0;

	key_v = ftok(PATH_SHM, PRI_SHM_ID);

	nshmid = shmget(key_v, 1024, IPC_CREAT|0666);
	if(nshmid == -1)
	{
		printf("create share memory failed\n");
		return 0;
	}

	p =  (char *)shmat(nshmid, 0, 0);
	if(p == NULL)
	{
		printf("get share memory error!\n");
		return 0;
	}

	printf("@_@ [%s]\n", p);

	shmdt(p);

	shmctl(nshmid, IPC_RMID, 0);

	return 0;
}