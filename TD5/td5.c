#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * thread(void * args);
static void cleanup(void *arg);

int main () {

	pthread_t tid;
	int max;

	printf("max > ");
	scanf("%d", &max);
	
	// création thread
	pthread_create(&tid, NULL, thread, &max);

	for(int i = 0; i < max/2; i++)	{
		printf("Main thread %d\n", (int) pthread_self());	
		usleep(1000);	
	}

	printf("Cancel\n");
	pthread_cancel(tid);
	
	usleep(1000);
	
	return 0;
}

void * thread(void * args) {

	int max = * (int *) args;

	pthread_mutex_lock(&mutex);

	pthread_cleanup_push(cleanup, NULL);

	printf("j'ai le mutex\n");
	for(int i = 0; i < max; i++)	{
		printf("Thread %d\n", (int) pthread_self());
		usleep(1000);	
	}

	pthread_mutex_unlock(&mutex);
	pthread_cleanup_pop(0);
	
	pthread_exit(NULL);
	return NULL;
}

static void cleanup(void *arg)	{
   printf("Called clean-up handler\n");
   pthread_mutex_unlock(&mutex);
}
