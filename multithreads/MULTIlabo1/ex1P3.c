#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

typedef struct {
    char* fichier;
    char* mot;
    int nbTabs;
} PARAM_THREAD;
void* FctThread(void* arg);
int main() {
    pthread_t th[4];
    int *res[4];

    PARAM_THREAD params[4] = {{"/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp", "printf", 0},{"/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp", "malloc", 1},{"/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp", "fork",   2},{"/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp", "signal", 3}};
    printf("[MAIN %d:%p] Demarrage\n", getpid(), pthread_self());
    for (int i = 0; i < 4; i++) {
        pthread_create(&th[i], NULL, FctThread, &params[i]);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(th[i], (void**)&res[i]);
    }
    printf("\nRESULTATS :\n");
    for (int i = 0; i < 4; i++) {
        printf("Thread %d : %d occurrences\n", i + 1, *res[i]);
        free(res[i]);
    }
    pthread_exit(NULL);
}
void* FctThread(void* arg) {
    PARAM_THREAD* p = (PARAM_THREAD*)arg;

    int fd, i = 0, compteur = 0;
    char temp[strlen(p->mot)];
    int* resultat = malloc(sizeof(int));

    while (1) {
        fd = open(p->fichier, O_RDONLY);
        if (fd < 0) 
            break;

        for (int t = 0; t < p->nbTabs; t++)
            printf("\t");
        printf("*\n");
        

        lseek(fd, i, SEEK_SET);
        int n = read(fd, temp, strlen(p->mot));
        close(fd);

        if (n < (int)strlen(p->mot)) 
            break;
        if (strncmp(temp, p->mot, strlen(p->mot)) == 0)
            compteur++;

        i++;
    }

    *resultat = compteur;
    pthread_exit(resultat);
}
