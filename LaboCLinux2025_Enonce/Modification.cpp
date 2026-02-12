#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <mysql.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"

int idQ, idSem;

int main()
{
  MESSAGE m, reponse;
  char nom[40];

    fprintf(stderr,"(MODIFICATION %d) Recuperation de l'id de la file de messages\n",getpid());
  idQ = msgget(CLE,0);
  if(idQ == -1)
  {
    perror("msgget modification");
    exit(1);
  }

    idSem = semget(CLE,1,0);
  if(idSem == -1)
  {
    perror("semget modification");
    exit(1);
  }

    fprintf(stderr,"(MODIFICATION %d) Lecture requete MODIF1\n",getpid());
  if(msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),getpid(),0) == -1)
  {
    perror("msgrcv MODIF1");
    exit(1);
  }

  strcpy(nom, m.data1);   
    fprintf(stderr,"(MODIFICATION %d) Prise non bloquante du sémaphore 0\n",getpid());
  struct sembuf op;
  op.sem_num = 0;
  op.sem_op  = -1;
  op.sem_flg = IPC_NOWAIT;

  if(semop(idSem,&op,1) == -1)
  {
        reponse.type = m.expediteur;
    reponse.requete = MODIF1;
    strcpy(reponse.data1,"KO");
    strcpy(reponse.data2,"KO");
    strcpy(reponse.texte,"KO");
    msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
    kill(m.expediteur,SIGUSR1);
    exit(0);
  }

    MYSQL *connexion = mysql_init(NULL);
  fprintf(stderr,"(MODIFICATION %d) Connexion à la BD\n",getpid());
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(MODIFICATION) Erreur connexion BD\n");
    exit(1);  
  }

    fprintf(stderr,"(MODIFICATION %d) Consultation en BD pour --%s--\n",getpid(),nom);

  char requete[200];
  MYSQL_RES *resultat;
  MYSQL_ROW tuple;

  sprintf(requete,"SELECT gsm,email FROM UNIX_FINAL WHERE nom='%s'", nom);
  mysql_query(connexion, requete);
  resultat = mysql_store_result(connexion);
  tuple = mysql_fetch_row(resultat);

    fprintf(stderr,"(MODIFICATION %d) Envoi de la reponse\n",getpid());

  reponse.type = m.expediteur;
  reponse.requete = MODIF1;
  strcpy(reponse.data1,"
    66459669+



    OK");
  strcpy(reponse.data2, tuple[0]);     strcpy(reponse.texte, tuple[1]);   
  msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
  kill(m.expediteur,SIGUSR1);

    fprintf(stderr,"(MODIFICATION %d) Attente requete MODIF2...\n",getpid());
  if(msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),getpid(),0) == -1)
  {
    perror("msgrcv MODIF2");
    exit(1);
  }

    fprintf(stderr,"(MODIFICATION %d) Modification en base de données pour --%s--\n",getpid(),nom);

  sprintf(requete,
          "UPDATE UNIX_FINAL SET gsm='%s', email='%s' WHERE nom='%s'",
          m.data2, m.texte, nom);
  mysql_query(connexion, requete);

  
  mysql_close(connexion);

    fprintf(stderr,"(MODIFICATION %d) Liberation du semaphore 0\n",getpid());
  op.sem_op = 1;
  semop(idSem,&op,1);

  exit(0);
}
