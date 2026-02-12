#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
void handlerSIGINT(int sig)
{
    printf("\n[THREAD %lu] recu signal SIGINT\n",pthread_self());
    pthread_exit(NULL);
}
void* Slave(void* arg)
{
    printf("[THREAD %lu] demarre et attends un signal\n",pthread_self());
    pause();   
    pthread_exit(NULL);
}
int main()
{
    pthread_t slaves[4];
    struct sigaction action;
    action.sa_handler = handlerSIGINT;

    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);

    printf("[MAIN %lu] demarrage du processus\n", pthread_self());
    for (int i = 0; i < 4; i++)
        pthread_create(&slaves[i], NULL, Slave, NULL);
    printf("[MAIN %lu] attends aussi un signal\n",pthread_self());
    
    pause();
    pthread_exit(NULL);
}
