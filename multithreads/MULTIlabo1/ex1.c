#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#define TRACE(message) printf("[THREAD %d:%p] %s",getpid(),pthread_self(),message);
void* FctThread1(void* p);
void* FctThread2(void* p);
void* FctThread3(void* p);
void* FctThread4(void* p);
int main() {
    pthread_t th1,th2,th3,th4;
    int* resultat1,*resultat2,*resultat3,*resultat4;
    printf("[MAIN %d:%p] Demarrage\n", getpid(), pthread_self());
    pthread_create(&th1, NULL, FctThread1, NULL);
    pthread_create(&th2, NULL, FctThread2, NULL);
    pthread_create(&th3, NULL, FctThread3, NULL);
    pthread_create(&th4, NULL, FctThread4, NULL);
    pthread_join(th1, (void**)&resultat1);
    pthread_join(th2, (void**)&resultat2);
    pthread_join(th3, (void**)&resultat3);
    pthread_join(th4, (void**)&resultat4);
    printf("\nRESULTATS :\n");
    printf("Thread 1 : %d occurrences\n", *resultat1);
    printf("Thread 2 : %d occurrences\n", *resultat2);
    printf("Thread 3 : %d occurrences\n", *resultat3);
    printf("Thread 4 : %d occurrences\n", *resultat4);
    free(resultat1);
    free(resultat2);
    free(resultat3);
    free(resultat4);
    pthread_exit(NULL);
}
void* FctThread1(void* p) {
    const char* FICHIER="/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp";
    const char* MOT = "printf";
    int fd;
    int i = 0;
    int compteur = 0;
    char temp[strlen(MOT)];
    int* resultat = malloc(sizeof(int));
    
    while(1){
        fd = open(FICHIER, O_RDONLY);
        printf("*");
        if(fd < 0){
            perror("erreur ouveture");
            break;
        }
        lseek(fd, i, SEEK_SET);
        int n = read(fd, temp, strlen(MOT));
        close(fd);
        
        if (n < (int)strlen(MOT)) {
            break;
        }
        if (strncmp(temp, MOT, strlen(MOT)) == 0) {
            compteur++;
        }
        i++;
    }
    *resultat = compteur;
    pthread_exit((void*)resultat);
}

void* FctThread2(void* p) {
    const char* FICHIER="/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp";
    const char* MOT = "malloc";
    int fd;
    int i = 0;
    int compteur = 0;
    char temp[strlen(MOT)];
    int* resultat = malloc(sizeof(int));
    
    while(1){
        fd = open(FICHIER, O_RDONLY);
        printf("\t*");
        if(fd < 0){
            perror("erreur ouveture");
            break;
        }
        lseek(fd, i, SEEK_SET);

        int n = read(fd, temp, strlen(MOT));
        
        close(fd);
        
        if (n < (int)strlen(MOT)) {
            break;
        }
        
        if (strncmp(temp, MOT, strlen(MOT)) == 0) {
            compteur++;
        }

        i++;
    }
    *resultat = compteur;
    pthread_exit((void*)resultat);
}

void* FctThread3(void* p) {
    const char* FICHIER="/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp";
    const char* MOT = "fork";
    int fd;
    int i = 0;
    int compteur = 0;
    char temp[strlen(MOT)];
    int* resultat = malloc(sizeof(int));
    
    while(1){
        fd = open(FICHIER, O_RDONLY);
        printf("\t\t*");
        if(fd < 0){
            perror("erreur ouveture");
            break;
        }
        lseek(fd, i, SEEK_SET);

        int n = read(fd, temp, strlen(MOT));
        
        close(fd);
        
        if (n < (int)strlen(MOT)) {
            break;
        }
        
        if (strncmp(temp, MOT, strlen(MOT)) == 0) {
            compteur++;
        }

        i++;
    }
    *resultat = compteur;
    pthread_exit((void*)resultat);
}

void* FctThread4(void* p) {
    const char* FICHIER="/home/student/Cpp-C/LaboCLinux2025_Enonce/Serveur.cpp";
    const char* MOT = "signal";
    int fd;
    int i = 0;
    int compteur = 0;
    char temp[strlen(MOT)];
    int* resultat = malloc(sizeof(int));
    
    while(1){
        fd = open(FICHIER, O_RDONLY);
        printf("\t\t\t*");
        if(fd < 0){
            perror("erreur ouveture");
            break;
        }
        lseek(fd, i, SEEK_SET);

        int n = read(fd, temp, strlen(MOT));
        
        close(fd);
        
        if (n < (int)strlen(MOT)) {
            break;
        }
        
        if (strncmp(temp, MOT, strlen(MOT)) == 0) {
            compteur++;
        }

        i++;
    }
    *resultat = compteur;
    pthread_exit((void*)resultat);
}