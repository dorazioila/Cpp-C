#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"

int idQ, idShm;

int main()
{
    sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask,SIGINT);
  sigprocmask(SIG_SETMASK,&mask,NULL);

    fprintf(stderr,"(PUBLICITE %d) Recuperation de l'id de la file de messages\n",getpid());
  idQ = msgget(CLE, 0);
  if(idQ == -1) { 
    perror("msgget pub"); 
    exit(1); 
  }

    fprintf(stderr,"(PUBLICITE %d) Recuperation de l'id de la mémoire partagée\n",getpid());
  idShm = shmget(CLE, 200, 0);
  if(idShm == -1) { 
    perror("shmget pub"); 
    exit(1); 
  }

  char *shmPub = (char*) shmat(idShm, NULL, 0);
  if(shmPub == (char*)-1) { 
    perror("shmat pub"); 
    exit(1); 
  }

    FILE *f = fopen("publicites.dat", "rb");
  if(!f)
  {
      perror("fopen publicites.dat");
      exit(1);
  }

  MESSAGE m;
  PUBLICITE pub;

  while(1)
{
    PUBLICITE pub;

    if(fread(&pub, sizeof(PUBLICITE), 1, f) != 1)
    {
        rewind(f);
        continue;
    }

        strncpy(shmPub, pub.texte, 199);
    shmPub[199] = '\0';

    MESSAGE m;
    m.type = 1;
    m.expediteur = getpid();
    m.requete = UPDATE_PUB;
    msgsnd(idQ, &m, sizeof(MESSAGE)-sizeof(long), 0);

        sleep(pub.nbSecondes);
}
}
