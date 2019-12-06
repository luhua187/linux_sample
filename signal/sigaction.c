#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void output(int sig)
{
	printf("get the signal [%d]\n", sig);
}


int main()
{
	struct sigaction act;
	act.sa_handler = output;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;

	sigaction(SIGINT, &act, 0);


	while(1);

	return 0;

}