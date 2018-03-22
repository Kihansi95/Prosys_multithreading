#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define SLEEP 10000 // 1ms 

int * px = NULL;
int * py = NULL;
pthread_mutex_t mutex_x = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t mutex_y = PTHREAD_MUTEX_INITIALIZER; 

void * thread1(void * args);
void * thread2(void * args);

int main () {

	pthread_t tid;
	int i, max;
	int x = 1;
	int y = 3;
	px = &x;
	py = &y;
	
	printf("max > ");
	scanf("%d", &max);

	// création thread
	pthread_create(&tid, NULL, thread1, &max);
	pthread_create(&tid, NULL, thread2, &max);

	// travailler sur px et py
	for(i = 0; i < max; i++)	{
		
	
		pthread_mutex_lock(&mutex_x);
		pthread_mutex_lock(&mutex_y);

		

		*px++; 
		*py=*py+1;


		printf("[T3] => *px++ = %d\n", *px); // [T3] => *px++ = 2.00000
		printf("[T3] => *py++ = %d\n", *py); // [T3] => *py++ = 4.00000
		*px--;
		*py = *py - 1;

		pthread_mutex_unlock(&mutex_y);
		pthread_mutex_unlock(&mutex_x);

		usleep(SLEEP);
	
	}

	// attendre de thread fini (pour récupérer)
	pthread_join(tid, NULL);
	
	return 0;	
}

void * thread1(void * args) {

	int x;
	int i;
	int max = * (int *) args;

	for(i = 0; i < max; i++) {
		pthread_mutex_lock(&mutex_x);

		// travailler sur px
		x = *px;
		*px = -1;
		printf("[T1] => *px = %d\n", x); // [T1] => *px = 1.00000
		*px = x;

		pthread_mutex_unlock(&mutex_x);

		usleep(0.8*SLEEP);
	}

	pthread_exit(NULL);
	return NULL;
}

void * thread2(void * args) {

	int y;
	int i;
	int max = * (int *) args;

	for(i = 0; i < max; i++) {
		pthread_mutex_lock(&mutex_y);

		// travailler sur py
		y = *py;
		*py = -1;
		printf("[T2] => *py = %d\n", y); // [T2] => *px = 2.00000
		*py = y;

		pthread_mutex_unlock(&mutex_y);

		usleep(0.5*SLEEP);
	}

	pthread_exit(NULL);
	return NULL;
}
