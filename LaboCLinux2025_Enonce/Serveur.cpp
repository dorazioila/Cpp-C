#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <mysql.h>
#include <setjmp.h>
#include "protocole.h" 
int idQ,idShm,idSem;
TAB_CONNEXIONS *tab;

void afficheTab();

MYSQL* connexion;

void handlerSIGINT(int sig)
{
    msgctl(idQ,IPC_RMID,NULL);
    shmctl(idShm, IPC_RMID, NULL);
    semctl(idSem, 0, IPC_RMID);
    mysql_close(connexion);
    exit(0);
}
void handlerSIGCHLD(int sig)
{
    int status;
    pid_t pid;

    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        fprintf(stderr,"(SERVEUR) Suppression du fils zombi %d\n", pid);

                for(int i=0;i<6;i++)
            if(tab->connexions[i].pidModification == pid)
                tab->connexions[i].pidModification = 0;
    }
}
int main()
{
    connexion = mysql_init(NULL);
  if (mysql_real_connect(connexion,"localhost","Student","PassStudent1_","PourStudent",0,0,0) == NULL)
  {
    fprintf(stderr,"(SERVEUR) Erreur de connexion à la base de données...\n");
    exit(1);  
  }

signal(SIGINT,handlerSIGINT);
signal(SIGCHLD, handlerSIGCHLD);
fprintf(stderr,"(SERVEUR %d) Creation de la file de messages\n",getpid());
idQ = msgget(CLE, IPC_CREAT | 0600);
if(idQ == -1)
{
    perror("msgget serveur");
    exit(1);
}

fprintf(stderr,"(SERVEUR %d) Creation de la mémoire partagée\n",getpid());
idShm = shmget(CLE, 200, IPC_CREAT | 0666);
if(idShm == -1)
{
    perror("shmget serveur");
    exit(1);
}

fprintf(stderr,"(SERVEUR %d) Creation du semaphore\n",getpid());
idSem = semget(CLE, 1, IPC_CREAT | 0600);
if(idSem == -1)
{
    perror("semget serveur");
    exit(1);
}

semctl(idSem, 0, SETVAL, 1);
char *shmPub = (char*) shmat(idShm, NULL, 0);
if(shmPub == (char*)-1)
{
    perror("shmat serveur");
    exit(1);
}

fprintf(stderr,"(SERVEUR %d) Initialisation de la table des connexions\n",getpid());
tab = (TAB_CONNEXIONS*) malloc(sizeof(TAB_CONNEXIONS)); 

for (int i=0 ; i<6 ; i++)
{
    tab->connexions[i].pidFenetre = 0;
    strcpy(tab->connexions[i].nom,"");
    for (int j=0 ; j<5 ; j++) tab->connexions[i].autres[j] = 0;
    tab->connexions[i].pidModification = 0;
}
tab->pidServeur1 = getpid();
tab->pidServeur2 = 0;
tab->pidAdmin = 0;
tab->pidPublicite = 0;

pid_t pid = fork();

if(pid == 0)
{
    execl("./Publicite", "Publicite", NULL);
    perror("execl Publicite");
    exit(1);
}
else
{
    tab->pidPublicite = pid;
}

afficheTab();


  
  int i,k,j;
  MESSAGE m;
  MESSAGE reponse;
  char requete[200];
  MYSQL_RES  *resultat;
  MYSQL_ROW  tuple;
  PUBLICITE pub;

  while(1)
  {
  	fprintf(stderr,"(SERVEUR %d) Attente d'une requete...\n",getpid());
    if (msgrcv(idQ,&m,sizeof(MESSAGE)-sizeof(long),1,0) == -1)
    {
        perror("(SERVEUR) Erreur de msgrcv");
        sleep(1);
        continue;  
    }
    pid_t pid;
    pid_t pidModif;
    switch(m.requete)
    {
      case CONNECT :  
      {
                      fprintf(stderr,"(SERVEUR %d) Requete CONNECT reçue de %d\n",getpid(),m.expediteur);
                      for(int i=0;i<6;i++)
                      if(tab->connexions[i].pidFenetre==0)
                      {
                          tab->connexions[i].pidFenetre = m.expediteur;
                          strcpy(tab->connexions[i].nom,"");
                          break;
                      }
                      }
                      break; 

      case DECONNECT :  
      {
                      fprintf(stderr,"(SERVEUR %d) Requete DECONNECT reçue de %d\n",getpid(),m.expediteur);
                      for(int i=0;i<6;i++)
                      if(tab->connexions[i].pidFenetre==m.expediteur)
                      {
                          tab->connexions[i].pidFenetre=0;
                          strcpy(tab->connexions[i].nom,"");
                      }
                      break; 
                      }

      case LOGIN :    

      {
                      bool dejaExiste = false;
                      fprintf(stderr,"(SERVEUR %d) Requete LOGIN reçue de %d : --%s--%s--%s--\n",
                      getpid(),m.expediteur,m.data1,m.data2,m.texte);

                        for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre == m.expediteur)
                          strcpy(tab->connexions[i].nom, m.data2);
                        sprintf(requete,"SELECT id FROM UNIX_FINAL WHERE nom='%s'",m.data2);
                        if(mysql_query(connexion, requete) != 0)
                        {
                            fprintf(stderr,"(SERVEUR) Erreur SELECT utilisateur\n");
                        }
                        else
                        {
                            resultat = mysql_store_result(connexion);
                            if(mysql_num_rows(resultat) == 0)
                            {
                                sprintf(requete,"INSERT INTO UNIX_FINAL (nom, gsm, email) VALUES('%s','---','---')",m.data2);
                                if(mysql_query(connexion, requete) != 0)
                                    fprintf(stderr,"(SERVEUR) Erreur INSERT utilisateur\n");
                                else
                                    fprintf(stderr,"(SERVEUR) Utilisateur %s ajouté en BD\n", m.data2);
                            }
                            else
                            {
                                dejaExiste = true;
                            }
                            mysql_free_result(resultat);
                        }
                      reponse.type = m.expediteur;
                      reponse.requete = LOGIN;
                      strcpy(reponse.data1,"OK");
                      if(dejaExiste)
                      {
                          sprintf(reponse.texte,"Re bienvenue %s", m.data2);
                      }
                      else
                      {
                          strcpy(reponse.texte,"Login réussi");
                      }
                      msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                      kill(m.expediteur,SIGUSR1);
                      for(i=0;i<6;i++)
                      {
                          if(tab->connexions[i].pidFenetre != 0 && tab->connexions[i].pidFenetre != m.expediteur)
                          {
                              reponse.type = tab->connexions[i].pidFenetre;
                              reponse.requete = SEND;

                              strcpy(reponse.data1, "SYSTEM");

                              sprintf(reponse.texte, "%s s'est connecté", m.data2);

                              msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                              kill(tab->connexions[i].pidFenetre, SIGUSR1);
                          }
                      }
                        for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre != 0 && tab->connexions[i].pidFenetre != m.expediteur && strlen(tab->connexions[i].nom) > 0)
                        {
                          reponse.type = tab->connexions[i].pidFenetre;
                          reponse.requete = ADD_USER;
                          strcpy(reponse.data1,m.data2);
                          fprintf(stderr,"[DEBUG SERVEUR] ADD_USER vers %d : %s\n",
                          tab->connexions[i].pidFenetre, m.data2);

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                          kill(tab->connexions[i].pidFenetre,SIGUSR1);
                        }

                        for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre != 0 &&tab->connexions[i].pidFenetre != m.expediteur && strlen(tab->connexions[i].nom) > 0)
                        {
                          reponse.type = m.expediteur;
                          reponse.requete = ADD_USER;
                          strcpy(reponse.data1,tab->connexions[i].nom);
                          fprintf(stderr,"[DEBUG SERVEUR] ADD_USER vers %d : %s\n",
                          m.expediteur, tab->connexions[i].nom);

                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                          kill(m.expediteur,SIGUSR1);
                        }
                    }
                    break;
                      

      case LOGOUT :  
      {
                      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT reçue de %d\n",getpid(),m.expediteur);
                      char nomSupprime[20]="";

                      for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre==m.expediteur)
                          strcpy(nomSupprime,tab->connexions[i].nom);
                      for(i=0;i<6;i++)
                      {
                          if(tab->connexions[i].pidFenetre != 0 && tab->connexions[i].pidFenetre != m.expediteur)
                          {
                              reponse.type = tab->connexions[i].pidFenetre;
                              reponse.requete = SEND;

                              strcpy(reponse.data1, "SYSTEM");
                              sprintf(reponse.texte, "%s s'est déconnecté", nomSupprime);

                              msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                              kill(tab->connexions[i].pidFenetre, SIGUSR1);
                          }
                      }
                      for(k=0;k<6;k++)
                        if(tab->connexions[k].pidFenetre != 0 && tab->connexions[k].pidFenetre != m.expediteur)
                        {
                          reponse.type = tab->connexions[k].pidFenetre;
                          reponse.requete = REMOVE_USER;
                          strcpy(reponse.data1,nomSupprime);
                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                          kill(tab->connexions[k].pidFenetre,SIGUSR1);
                        }

                      for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre==m.expediteur)
                        {
                          tab->connexions[i].pidFenetre=0;
                          strcpy(tab->connexions[i].nom,"");
                          for(j=0;j<5;j++) tab->connexions[i].autres[j]=0;
                        }

                      for(i=0;i<6;i++)
                        for(j=0;j<5;j++)
                          if(tab->connexions[i].autres[j]==m.expediteur)
                            tab->connexions[i].autres[j]=0;
                    }
                    break;
                      

      case ACCEPT_USER :
      {
                      fprintf(stderr,"(SERVEUR %d) Requete ACCEPT_USER reçue de %d\n",getpid(),m.expediteur);
                      int pidDest=0;

                      for(i=0;i<6;i++)
                        if(strcmp(tab->connexions[i].nom,m.data1)==0)
                          pidDest = tab->connexions[i].pidFenetre;

                      for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre==m.expediteur)
                          for(j=0;j<5;j++)
                            if(tab->connexions[i].autres[j]==0)
                            {
                              tab->connexions[i].autres[j]=pidDest;
                              break;
                            }
                      break;
                      }

      case REFUSE_USER :
      {
                      fprintf(stderr,"(SERVEUR %d) Requete REFUSE_USER reçue de %d\n",getpid(),m.expediteur);
                      int pidDest=0;

                      for(i=0;i<6;i++)
                        if(strcmp(tab->connexions[i].nom,m.data1)==0)
                          pidDest = tab->connexions[i].pidFenetre;

                      for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre==m.expediteur)
                          for(j=0;j<5;j++)
                            if(tab->connexions[i].autres[j]==pidDest)
                              tab->connexions[i].autres[j]=0;
                      break;
                      }

      case SEND : 
      {
                      fprintf(stderr,"(SERVEUR %d) Requete SEND reçue de %d\n",getpid(),m.expediteur);
                      char nomExp[20];
                      int ligne=-1;

                      for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre==m.expediteur)
                        {
                          strcpy(nomExp,tab->connexions[i].nom);
                          ligne=i;
                          break;
                        }

                      for(j=0;j<5;j++)
                      {
                        int pidDest = tab->connexions[ligne].autres[j];
                        if(pidDest!=0)
                        {
                          reponse.type = pidDest;
                          reponse.requete = SEND;
                          strcpy(reponse.data1,nomExp);
                          strcpy(reponse.texte,m.texte);
                          msgsnd(idQ,&reponse,sizeof(MESSAGE)-sizeof(long),0);
                          kill(pidDest,SIGUSR1);
                        }
                      }
                      break; 
                      }

      case UPDATE_PUB :
      {
                      fprintf(stderr,"(SERVEUR %d) Requete UPDATE_PUB reçue de %d\n",getpid(),m.expediteur);
                      for(int i=0 ; i<6 ; i++)
                      {
                          if(tab->connexions[i].pidFenetre  != 0)
                          {
                              kill(tab->connexions[i].pidFenetre , SIGUSR2);
                          }
                      }
                      break;}

      case CONSULT :
                     {
                      fprintf(stderr,"(SERVEUR %d) Requete CONSULT reçue de %d : %s\n",
                      getpid(), m.expediteur, m.data1);

                      pid = fork();

                      if(pid == 0)
                      {
                          execl("./Consultation", "Consultation", NULL);
                          perror("execl Consultation");
                          exit(1);
                      }
                      else
                      {
                          m.type = pid;
                          msgsnd(idQ, &m, sizeof(MESSAGE)-sizeof(long), 0);
                      }
                      break;
                          }

      case MODIF1 :
                      fprintf(stderr,"(SERVEUR %d) Requete MODIF1 reçue de %d\n",getpid(),m.expediteur);

                          for(i=0;i<6;i++)
                          if(tab->connexions[i].pidFenetre == m.expediteur)
                              strcpy(m.data1, tab->connexions[i].nom);

                      pid = fork();

                      if(pid == 0)
                      {
                          execl("./Modification","Modification",NULL);
                          perror("execl Modification");
                          exit(1);
                      }
                      else
                      {
                              for(i=0;i<6;i++)
                              if(tab->connexions[i].pidFenetre == m.expediteur)
                                  tab->connexions[i].pidModification = pid;
                                  m.type = pid;
                          msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0);
                      }
                      break;

      case MODIF2 :
      {
                      fprintf(stderr,"(SERVEUR %d) Requete MODIF2 reçue de %d\n",getpid(),m.expediteur);

                      pidModif = 0;
                      for(i=0;i<6;i++)
                        if(tab->connexions[i].pidFenetre == m.expediteur)
                          pidModif = tab->connexions[i].pidModification;
                          m.type = pidModif;
                      msgsnd(idQ,&m,sizeof(MESSAGE)-sizeof(long),0);

                      break;
                      }

      case LOGIN_ADMIN :
                      fprintf(stderr,"(SERVEUR %d) Requete LOGIN_ADMIN reçue de %d\n",getpid(),m.expediteur);
                      break;

      case LOGOUT_ADMIN :
                      fprintf(stderr,"(SERVEUR %d) Requete LOGOUT_ADMIN reçue de %d\n",getpid(),m.expediteur);
                      break;

      case NEW_USER :
                      fprintf(stderr,"(SERVEUR %d) Requete NEW_USER reçue de %d : --%s--%s--\n",getpid(),m.expediteur,m.data1,m.data2);
                      break;

      case DELETE_USER :
                      fprintf(stderr,"(SERVEUR %d) Requete DELETE_USER reçue de %d : --%s--\n",getpid(),m.expediteur,m.data1);
                      break;

      case NEW_PUB :
                      fprintf(stderr,"(SERVEUR %d) Requete NEW_PUB reçue de %d\n",getpid(),m.expediteur);
                      break;
    }
    afficheTab();
  }
}

void afficheTab()
{
  fprintf(stderr,"Pid Serveur 1 : %d\n",tab->pidServeur1);
  fprintf(stderr,"Pid Serveur 2 : %d\n",tab->pidServeur2);
  fprintf(stderr,"Pid Publicite : %d\n",tab->pidPublicite);
  fprintf(stderr,"Pid Admin     : %d\n",tab->pidAdmin);
  for (int i=0 ; i<6 ; i++)
    fprintf(stderr,"%6d -%20s- %6d %6d %6d %6d %6d - %6d\n",tab->connexions[i].pidFenetre,
                                                      tab->connexions[i].nom,
                                                      tab->connexions[i].autres[0],
                                                      tab->connexions[i].autres[1],
                                                      tab->connexions[i].autres[2],
                                                      tab->connexions[i].autres[3],
                                                      tab->connexions[i].autres[4],
                                                      tab->connexions[i].pidModification);
  fprintf(stderr,"\n");
}

