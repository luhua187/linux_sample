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

	msg.type = 5;
	strncpy(msg.data, "wuluhua!", 8);

	msgsnd(nmsgid, &msg, 256, 0);

	return 0;
}