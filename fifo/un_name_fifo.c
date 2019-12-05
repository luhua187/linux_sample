

/***************************
1.只能用于有共同祖先或者亲缘关系的进程，通常一个管道由一个进程创建，然后该进程调用fork函数，之后父子进程就可以使用该管道。
2.管道提供流式服务
3.管道的生命周期跟随进程终止
4.管道是半双工的，数据只能向一个方向流动，需要数据互通时需建立两个管道。
5.管道是面向字节流传输数据的：
  面向字节流：收发数据比较灵活，数据无规则发送，数据无边界。
  面向数据报：数据只能整条接收
6.管道自带同步与互斥
  临界资源：大家都能访问的公共资源
  临界区：对临界资源进行操作的代码
  同步：访问的可控时序性
  互斥：对临界资源的同一时间内唯一访问性（保护临界资源的安全）

*************************************/


//fd[0]只读，fd[1]只写；

#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	pid_t pid;
	int fd[2];
	int r_len, w_len;
	char buf[256];

	if(pipe(fd) < 0)
	{
		printf("pipe create error\n");
		return 0;
	}

	pid = fork();
	if(pid == 0)  //子进程
	{
		close(fd[0]);
		write(fd[1], "1234567890",10);
		close(fd[1]);
		return 0;
	}
	else if(pid > 0) //父进程
	{
		close(fd[1]);
		read(fd[0],buf, 20);
		printf("Q_Q:[%s]\n", buf);
		waitpid(pid, NULL, 0);
	}
	return 0;
}