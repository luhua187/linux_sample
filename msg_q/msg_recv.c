#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/msg.h>

#define PRI_SHM_ID 1024
#define PATH_SHM "home/lu/"

typedef struct _a
{
	long type;
	char data[256];
}msg_t;

int main()
{
	key_t key_v = 0;
	msg_t msg;
	int nmsgid = 0;

	key_v = ftok(PATH_SHM, PRI_SHM_ID);
	nmsgid = msgget(key_v, IPC_CREAT|0666);


	msgrcv(nmsgid, &msg, sizeof(msg_t), (long)5,0);

	printf("T_T [%s]\n", msg.data);

	msgctl(nmsgid, IPC_RMID, NULL);

	return 0;

}