#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>

#define N 20

typedef struct {
	int id;
} args_thread;

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_key_t	key;

void * thread(void * args);
void fonction_init();
int incrementation();

int main () {

	args_thread targ_1;
	args_thread targ_2;
	args_thread targ_3;

	pthread_t tid_1;
	pthread_t tid_2;
	pthread_t tid_3;

	// thread 1 demande 3 ressources
	targ_1.id = 1; 
	targ_2.id = 2; 
	targ_3.id = 3; 

	// create 3 threads 
	pthread_create(&tid_1, NULL, thread, &targ_1);
	pthread_create(&tid_2, NULL, thread, &targ_2);
	pthread_create(&tid_3, NULL, thread, &targ_3);

	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
	pthread_join(tid_3, NULL);
	return 0;
}

void * thread(void * args) {

	pthread_once(&once, fonction_init);

	// allouer variable spécifique
	void * value = malloc(sizeof(int));
	pthread_setspecific(key, (void *) value);
	
	args_thread monarg = * (args_thread *) args;
	int id = monarg.id;
	
	for(int i = 0; i < N; i ++)	{
		int static_i = incrementation();
		pthread_setspecific(key, &static_i);
		//printf("Thread[%d] hey hey : %d\n", (int) pthread_self(), static_i);
		printf("Thread[%d] hey hey : %d\n", id, static_i);
		usleep(1000);
	}
	
	pthread_exit(NULL);
	return NULL;
}

void fonction_init()	{
	printf("fonction_init\n");
	// init key
	int status;
	if ((status = pthread_key_create(&key, NULL )) < 0) {
		printf("pthread_key_create failed, errno=%d", errno);
		exit(1);
	 }
}

int incrementation()	{
	int i = *(int*) pthread_getspecific(key);
	i++;
	return i;
}
