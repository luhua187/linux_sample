#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

const char *fifo_name="./my_fifo";


int main()
{
	int pipe_fd;
	int res = 0;
	char buf[64];

	if(access(fifo_name, F_OK) == -1)
	{
		res = mkfifo(fifo_name, 0777);
		if(res != 0)
		{
			printf("create fifo fiie error!\n");
			return 0;
		}
	}

	pipe_fd = open(fifo_name, O_RDWR);

	read(pipe_fd, buf, 64);
	printf("Q_Q:[%s]\n",buf);
	
	write(pipe_fd, "12345", 5);
	


	return 0;

}