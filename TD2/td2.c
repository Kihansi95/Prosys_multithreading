#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * handler();

float * px = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

int main () {

	pthread_t tid;
	int max;
	float x = 1;
	px = &x;
	
	printf("max > ");
	scanf("%d", &max);

	// création thread
	pthread_create(&tid, NULL, handler, &max);

	// boucle M fois 
	for (int i = 0; i < max; i++) {
		
		// début de section critique
		pthread_mutex_lock(&mutex);
		px = NULL;
		printf("Main thread: i = %d\n", i);
		px = &x;
		pthread_mutex_unlock(&mutex);

		usleep(1000);
	}

	// attendre de thread fini (pour récupérer)
	pthread_join(tid, NULL);
	
	return 0;	
}

void * handler(void * args) {
	int max = * (int *) args;
	for (int i = 0; i < max; i++)	{

		pthread_mutex_lock(&mutex);
		printf("[i = %d] *px = %f\n", i, *px);
		pthread_mutex_unlock(&mutex);
	
		usleep(800);
	}

	pthread_exit(NULL);
	return NULL;
}
