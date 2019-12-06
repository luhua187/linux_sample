#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handler(int arg)
{
	printf("\n recv ctrl+c\n");

	kill(getpid(), 9);
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, handler);
	while(1);
	return 0;
}