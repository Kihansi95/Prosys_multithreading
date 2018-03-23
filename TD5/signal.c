#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void handler(int sig);

int main () {
	sigset_t mask;


	sigfillset(&mask);
	sigdelset(&mask, SIGUSR1);

	signal(SIGUSR1, handler);
 
	if (sigprocmask(SIG_SETMASK, &mask, NULL) < 0) {
		perror ("sigprocmask");
		return 1;
	}

	while(1);
	return 0;
}

void handler(int sig)	{
	printf("Vanessa est estupidaaaaa!!!!\n");
}

