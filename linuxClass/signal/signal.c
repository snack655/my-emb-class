#include <signal.h>
#include <unistd.h>
#include <stdio.h>

void sig_handler(int signo);

int main(int argc, char **argv)
{
	int i = 0;
	signal(SIGINT, (void *)sig_handler);
	while(1)
	{
		printf("%d\n", i);
		sleep(2);
		i++;
	}
}

void sig_handler(int signo)
{
	printf("I Received SIGINT (%d)\n", SIGINT);
}
