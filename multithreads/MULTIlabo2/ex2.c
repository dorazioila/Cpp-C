#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
void handlerSIGINT(int sig)
{
    printf("\n[THREAD %lu] recu signal SIGINT\n",pthread_self());
}
void* Slave(void* arg)
{
    printf("[THREAD %lu] thread secondaire\n",pthread_self());
    pause();   
    pthread_exit(NULL);
}

void* Master(void* arg)
{
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_UNBLOCK, &set, NULL);

    printf("[MASTER %lu] le seul a pouvoir recevoir SIGINT\n",pthread_self());
    while (1)
        pause();   
    pthread_exit(NULL);
}

int main()
{
    pthread_t master;
    pthread_t slaves[3];
    sigset_t set;
    struct sigaction action;
    action.sa_handler = handlerSIGINT;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &set, NULL);
    printf("[MAIN %lu] SIGINT masque dans le main\n", pthread_self());
    for (int i = 0; i < 3; i++)
        pthread_create(&slaves[i], NULL, Slave, NULL);
    pthread_create(&master, NULL, Master, NULL);

    pthread_exit(NULL);
}
