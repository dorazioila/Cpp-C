#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
void handlerSIGINT(int sig)
{
    printf("\n[THREAD %lu] recu signal SIGINT\n",pthread_self());
    kill(getpid(),SIGUSR1) ;
}

void handlerSIGUSR1(int sig)
{
    printf("[SLAVE %lu] recu SIGUSR1\n", pthread_self());
    pthread_exit(NULL);
}

void* Slave(void* arg)
{
    sigset_t set;
    struct sigaction action;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    action.sa_handler = handlerSIGUSR1;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGUSR1, &action, NULL);

    printf("[SLAVE %lu] Pret a recevoir SIGUSR1\n", pthread_self());
    pause();
    pthread_exit(NULL);
}


void* Master(void* arg)
{
    sigset_t set;
    struct sigaction action;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    sigemptyset(&set);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &set, NULL);

    action.sa_handler = handlerSIGINT;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    printf("[MASTER %lu] le seul a pouvoir recevoir SIGINT\n",pthread_self());
    while (1)
        pause();   
    pthread_exit(NULL);
}

int main()
{
    pthread_t master;
    pthread_t slaves[4];
    sigset_t set;
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGUSR1);
    
    pthread_sigmask(SIG_SETMASK, &set, NULL);
    printf("[MAIN %lu] SIGINT masque dans le main\n", pthread_self());
    for (int i = 0; i < 3; i++)
        pthread_create(&slaves[i], NULL, Slave, NULL);
    pthread_create(&master, NULL, Master, NULL);

     for (int i = 0; i < 4; i++)
        pthread_join(slaves[i], NULL);

    printf("[MAIN] Tous les slaves sont termines\n");

    pthread_exit(NULL);
}
