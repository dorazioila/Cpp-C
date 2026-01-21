#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <mysql.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"

int idQ;

int main()
{
  MESSAGE m, reponse;
  char nom[40];

  // Récupération file de messages
  fprintf(stderr,"(CONSULTATION %d) Recuperation de l'id de la file de messages\n",getpid());
  idQ = msgget(CLE,0);
  if(idQ == -1)
  {
    perror("msgget CONSULTATION");
    exit(1);
  }

  // Lecture requête CONSULT
  fprintf(stderr,"(CONSULTATION %d) Lecture requete CONSULT\n",getpid());
  if(msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),getpid(),0) == -1)
  {
    perror("msgrcv CONSULT");
    exit(1);
  }

  strcpy(nom, m.data1);

  // Connexion BD
  MYSQL *connexion = mysql_init(NULL);
  fprintf(stderr,"(CONSULTATION %d) Connexion à la BD\n",getpid());
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(CONSULTATION) Erreur connexion BD\n");
    exit(1);  
  }

  // Recherche infos
  fprintf(stderr,"(CONSULTATION %d) Consultation en BD pour --%s--\n",getpid(),nom);

  char requete[200];
  MYSQL_RES *resultat;
  MYSQL_ROW tuple;

  sprintf(requete,"SELECT gsm,email FROM UNIX_FINAL WHERE nom='%s'", nom);
  mysql_query(connexion, requete);
  resultat = mysql_store_result(connexion);

  reponse.type = m.expediteur;
  reponse.requete = CONSULT;

  if(resultat && (tuple = mysql_fetch_row(resultat)) != NULL)
  {
    strcpy(reponse.data1,"OK");
    strcpy(reponse.data2, tuple[0]);   // gsm
    strcpy(reponse.texte, tuple[1]);   // email
  }
  else
  {
    strcpy(reponse.data1,"KO");
    reponse.data2[0] = 0;
    reponse.texte[0] = 0;
  }

  mysql_free_result(resultat);
  mysql_close(connexion);

  // Envoi réponse au client
  fprintf(stderr,"(CONSULTATION %d) Envoi de la reponse\n",getpid());
  msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
  kill(m.expediteur,SIGUSR1);

  exit(0);
}
