#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#define TRACE(message) printf("[THREAD %d:%p] %s",getpid(),pthread_self(),message);
pthread_mutex_t mutexParam = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexCompteur = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condCompteur = PTHREAD_COND_INITIALIZER;
pthread_key_t cle;
int compteur = 0;
typedef struct
{
    char nom[20];
    int nbSecondes;
} DONNEE;
DONNEE Param;
DONNEE data[] = { 
    "MATAGNE", 2,   
    "WILVERS", 3,
    "WAGNER", 1,
    "QUETTIER", 2,
    "", 0 };
void destructeur(void* p) {
    free(p);
}
void handlerSIGINT(int sig) {
    char* nom = pthread_getspecific(cle);
    printf("Thread %d.%lu s’occupe de \"%s\"\n",
           getpid(), pthread_self(), nom);
}
void* fonction_thread(void* arg)
{
	DONNEE* local = (DONNEE*)arg;
    char* nom = malloc(strlen(local->nom)+1);
    struct sigaction sa;
    sa.sa_handler = handlerSIGINT;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    sigset_t set;
    sigemptyset(&set);
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    strcpy(nom, local->nom);
    pthread_setspecific(cle, nom);
    pid_t pid = getpid();               
    pthread_t tid = pthread_self(); 

    printf("Thread %d.%lu lancé\n", pid, tid);
    printf("Nom : %s\n", local->nom);

    struct timespec t;
    t.tv_sec = local->nbSecondes;
    t.tv_nsec = 0;
    nanosleep(&t, NULL);
    printf("Thread %d.%lu se termine\n", pid, tid);

    pthread_mutex_lock(&mutexCompteur);
    compteur--;
    printf("[THREAD %d:%p] compteur = %d\n", getpid(), pthread_self(), compteur);
    if(compteur==0){
    	pthread_cond_signal(&condCompteur);
    }
    pthread_mutex_unlock(&mutexCompteur);
    free(local);
    pthread_exit(NULL);
}

int main()
{
    pthread_key_create(&cle, destructeur);
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_SETMASK, &set, NULL);
    pthread_t threads[10]; 
    char txt[80];
    int i;
    for (i = 0; data[i].nbSecondes != 0; i++) {
    	pthread_mutex_lock(&mutexCompteur);
    	compteur++;
    	pthread_mutex_unlock(&mutexCompteur);
        
        DONNEE* param_thread = malloc(sizeof(DONNEE));
        memcpy(param_thread, &data[i], sizeof(DONNEE));
        pthread_create(&threads[i], NULL, fonction_thread, param_thread);
    }
    
    pthread_mutex_lock(&mutexCompteur);
    while(compteur != 0){
    	pthread_cond_wait(&condCompteur, &mutexCompteur);
    	sprintf(txt,"Main : Notification reçue (compteur = %d)\n",compteur);
 		TRACE(txt);
    }
    pthread_mutex_unlock(&mutexCompteur);
    printf("Tous les threads sont terminés\n");
    return 0;
}
