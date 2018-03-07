#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * handler();

float * px = NULL;
float * py = NULL;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

int main () {

	pthread_t tid;
	int max;
	float x = 1;
	float y = 2;
	px = &x;
	py = &y;
	
	printf("max > ");
	scanf("%d", &max);

	// création thread
	pthread_create(&tid, NULL, thread1, &max);
	pthread_create(&tid, NULL, thread2, &max);

	// travailler sur px et py
	

	// attendre de thread fini (pour récupérer)
	pthread_join(tid, NULL);
	
	return 0;	
}

void * thread1(void * args) {
	// travailler sur px

	pthread_exit(NULL);
	return NULL;
}

void * thread2(void * args) {
	// travailler sur py

	pthread_exit(NULL);
	return NULL;
}
