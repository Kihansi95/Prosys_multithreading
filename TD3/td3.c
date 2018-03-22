#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define M 4

struct args_thread {
	int id;
	int nbres;
	int max;
};

int 				res_disponible 	= 4; 		// cpt de ressources disponible
pthread_mutex_t 	mutex_res 		= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t		mutex_cond 		= PTHREAD_COND_INITIALIZER;
pthread_mutex_t		mutex_wait		= PTHREAD_MUTEX_INITIALIZER;

void * thread(void * args);

int main () {
	int max;

	pthread_t tid_1;
	pthread_t tid_2;
	pthread_t tid_3;
	struct args_thread targ_1;
	struct args_thread targ_2;
	struct args_thread targ_3;

	// init args threads
	printf("max > ");
	scanf("%d", &max);
	// thread 1 demande 3 ressources
	targ_1.id = 1; targ_1.nbres = 3;	targ_1.max = max;
	targ_2.id = 2; targ_2.nbres = 2;	targ_2.max = max;
	targ_3.id = 3; targ_3.nbres = 1;	targ_3.max = max;


	// create 3 threads 
	pthread_create(&tid_1, NULL, thread, &targ_1);
	pthread_create(&tid_2, NULL, thread, &targ_2);
	pthread_create(&tid_3, NULL, thread, &targ_3);

	// attendre de thread fini (pour récupérer)
	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
	pthread_join(tid_3, NULL);

	return 0;
}

void * thread(void * args) {
		
	int i;
	struct args_thread monarg = * (struct args_thread *) args;
	int id = monarg.id;
	int	nb_res = monarg.nbres;
	int max = monarg.max;
	int access = 0;

	// test if ressources dispo
	for (i = 0; i < max; i++)	{
		do	{
			printf("Thread %d demande %d ressource(s) pour %d-ème fois...\n", id, nb_res, i+1);

			pthread_mutex_lock(&mutex_res);	// bloque quand je vérif nb_res
			printf("[Thread %d] disponible = %d, demande = %d\n", id, res_disponible, nb_res);

			if(res_disponible >= nb_res) {
					
				access = 1;				// Je peux utiliser
				res_disponible -= nb_res;	
				printf("[Thread %d] utilise %d ressource(s), restant = %d\n", id, nb_res, res_disponible);
			}
			pthread_mutex_unlock(&mutex_res);
	
			if(access)	{
				usleep(800);

				pthread_mutex_lock(&mutex_res);
				res_disponible += nb_res;
				pthread_mutex_unlock(&mutex_res);
				pthread_cond_broadcast(&mutex_cond);

				printf("[Thread %d] Fini, reveiller tout le monde \n", id);
			}

			if(!access)	{
				printf("[Thread %d] ressource non suffisant, waiting... \n", id);
				pthread_cond_wait(&mutex_cond, &mutex_wait);
			}
			
		}	while (!access);
	}
	
	pthread_exit(NULL);
	return NULL;
}
