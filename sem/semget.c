/****************************
int semget(key_t key, int nsems, int semflg);
功能：用来创建和访问一个信号量集
key：信号量集的key值
nsems：信号集中的信号量的个数；
semflag：由9个权限标志构成，；


int semctl(int semid, int semnum, int cmd, ...);
功能：用户控制信号量集，主要用于信号量的初始化操作；
semid：是semget的返回值；
semnum：信号集中信号量的序号；(从0开始，指定需要的操作的信号量集中的信号)
cmd：将要采取的动作（5个可能取值）
可变参数：根据cmd命令的不同，而不同；


int semop(int semid, struct sembuf *sops, unsigned nsops)
功能：主要实现的是PV操作；

semID：semget返回的id值
sops：struct sembuf 结构体；
nsops：是指每次操作的个数，即sops的个数；semop一次可以操作多个信号；

struct sembuf
{
	unsigned short sem_num;
	short  sem_op;
	short  sem_flg;
}
sem_num:操作信号在信号集中的编号，第一个信号的编号是0:
sem_op：如果其值是正值（1、2），该值会加到现有值中，相当于释放使用的资源；如果sem_op为负值（-1、-2）
则相当于请求此数值需求的资源；
sem_flg有两种选择：
   IPC_NOWAIT 对信号操作不能满足时，semop不阻塞，立即返回，同时设置错误信息；
   IPC_UNDO 程序结束时，保证信号值会被重设为semop()调用前的值；避免程序异常退出，造成资源锁定
*****************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>


union semun
{
	int val; //value for SETVAL
	struct  semid_ds *buf; // buffer for IPC_STAT, IPC_SET
	unsigned short *array; //array for GETALL, SETALL
	struct seminfo *__buf; // buffer for IPC_INFO
};

 /***************
 ***************/

int sem_setval(int semid, int val)
{
	int ret = 0;

	//union semun必须自定义
	union semun su;
	su.val = val;

	//semctl()第二参数是序号，这是0代表设置信号集中的第一个信号量的值；
	ret = semctl(semid, 0, SETVAL, su);
	if(ret == -1)
	{
		perror("semctl() error,,,,,,,,,");
	}

	return ret;
}


int sem_getval(int semid)
{
	int ret = 0;
	//setctl()第二参数是信号集中的序号，0代表第一个信号
	//当使用GETVAL命令时，调用中的最后一个参数忽略，默认填0

	ret = semctl(semid, 0, GETVAL, 0);
	if(ret == -1)
	{
		perror("semctl() error,,,,,,");
	}
	printf("getval = %d\n", ret);
	return ret;
}

//等待资源，P操作。
int sem_p(int semid)
{
	int ret = 0;

	//通过struct sembuf 结构体中的sem_op的属性设置P操作；
	struct sembuf sbuf={0, -1, 0};
	ret = semop(semid, &sbuf, 1);
	if(ret == -1)
	{
		perror("semctl() error,,,,,,,,,");
	}

	return ret;
}

//释放资源，V操作
int sem_v(int semid)
{
	int ret = 0;

	//通过struct sembuf 结构体中的sem_op的属性设置V操作；
	struct sembuf sbuf={0, 1, 0};
	ret = semop(semid, &sbuf, 1);
	if(ret == -1)
	{
		perror("semctl() error,,,,,,,,,");
	}
	return ret;
}

int main()
{
	int semid = 0;

	semid = semget(0x1234, 1, 0666 | IPC_CREAT );
	if(semid == -1)
	{
		perror("semget() err");
        return -1;
	}

	sem_setval(semid, 1);
	sem_getval(semid);

	sem_p(semid);
	printf("12345678...........\n");
	sem_v(semid);

	return 0;
}








































