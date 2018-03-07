#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SLEEP 1000000 // 1 seconde

void * handler();

int main () {

	pthread_t tid;
	int M; // M fois dans le thread principal
	int N; // N fois dans le thread

	// demander pour M et N
	printf("M > ");
	scanf("%d", &M);
	printf("N > ");
	scanf("%d", &N);

	printf ("M = %d, N = %d:\n", M, N);

	// création thread
	pthread_create(&tid, NULL, handler, &N);

	// boucle M fois 
	for (int i = 0; i < M; i++) {
		printf("coucou %d\n", i);	
		usleep(SLEEP);
	}

	// attendre de thread fini (pour récupérer)
	pthread_cancel(tid);
	
	return 0;	
}

void * handler(void * args) {
	int N = * (int *) args;
	for (int i = 0; i < N; i++)	{
		printf("et mon courroux : %d\n", i);	
		usleep(SLEEP);
	}

	pthread_exit(NULL);
	return NULL;
}
