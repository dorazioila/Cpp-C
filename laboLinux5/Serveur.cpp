#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include "protocole.h"

int idQ;
int pid1, pid2;

//Handler de signal SIGINT (Étape 6)
void handlerSIGINT(int sig)
{
  fprintf(stderr,"\n(SERVEUR) Reception du signal SIGINT (Ctrl+C)\n");
  
  // Suppression de la file de messages
  fprintf(stderr,"(SERVEUR) Suppression de la file de messages...\n");
  if(msgctl(idQ, IPC_RMID, NULL) == -1){
    perror("msgctl IPC_RMID");
    exit(1);
  }
  
  fprintf(stderr,"(SERVEUR) File de messages supprimee avec succes\n");
  fprintf(stderr,"(SERVEUR) Arret du serveur\n");
  exit(0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonction principale ////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
  MESSAGE requete;
  MESSAGE reponse;
  pid_t destinataire;

  // Armement du signal SIGINT (Étape 6)
  fprintf(stderr,"(SERVEUR) Armement du signal SIGINT\n");
  struct sigaction sa;
  sa.sa_handler = handlerSIGINT;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  
  if(sigaction(SIGINT, &sa, NULL) == -1){
    perror("sigaction");
    exit(1);
  }
  fprintf(stderr,"(SERVEUR) Signal SIGINT arme avec succes\n");

  // Creation de la file de message
  fprintf(stderr,"(SERVEUR) Creation de la file de messages\n");
  if ((idQ = msgget(CLE, IPC_CREAT | IPC_EXCL | 0600)) == -1){
    perror("msgget");
    exit(1);
  }
  fprintf(stderr,"(SERVEUR) File creee avec idQ = %d\n", idQ);
  
  // Initialisation des PIDs clients
  pid1 = 0;
  pid2 = 0;

  // Attente de connection du premier client
  fprintf(stderr,"(SERVEUR) Attente de connection d'un premier client...\n");
  if(msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0) == -1){
    perror("msgrcv client 1");
    msgctl(idQ, IPC_RMID, NULL);
    exit(1);
  }
  
  fprintf(stderr,"(SERVEUR) Message recu - expediteur: %d, texte: '%s'\n", 
          requete.expediteur, requete.texte);
  
  // Vérification que c'est bien un message de connexion
  if(strcmp(requete.texte, "CONNEXION") == 0){
    pid1 = requete.expediteur;
    fprintf(stderr,"(SERVEUR) Premier client connecte : PID = %d\n", pid1);
  }
  else{
    fprintf(stderr,"(SERVEUR) ERREUR : Message de connexion attendu, recu: '%s'\n", 
            requete.texte);
    fprintf(stderr,"(SERVEUR) Expediteur: %d\n", requete.expediteur);
    msgctl(idQ, IPC_RMID, NULL);
    exit(1);
  }
  
  // Attente de connection du second client
  fprintf(stderr,"(SERVEUR) Attente de connection d'un second client...\n");
  if(msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0) == -1){
    perror("msgrcv client 2");
    msgctl(idQ, IPC_RMID, NULL);
    exit(1);
  }
  
  fprintf(stderr,"(SERVEUR) Message recu - expediteur: %d, texte: '%s'\n", 
          requete.expediteur, requete.texte);
  
  // Vérification que c'est bien un message de connexion
  if(strcmp(requete.texte, "CONNEXION") == 0){
    pid2 = requete.expediteur;
    fprintf(stderr,"(SERVEUR) Second client connecte : PID = %d\n", pid2);
  }
  else{
    fprintf(stderr,"(SERVEUR) ERREUR : Message de connexion attendu, recu: '%s'\n", 
            requete.texte);
    fprintf(stderr,"(SERVEUR) Expediteur: %d\n", requete.expediteur);
    fprintf(stderr,"(SERVEUR) Peut-etre que le client 1 a envoye un message avant que le client 2 se connecte?\n");
    msgctl(idQ, IPC_RMID, NULL);
    exit(1);
  }
  
  fprintf(stderr,"\n========================================\n");
  fprintf(stderr,"(SERVEUR) Les deux clients sont connectes!\n");
  fprintf(stderr,"  CLIENT 1 : PID = %d\n", pid1);
  fprintf(stderr,"  CLIENT 2 : PID = %d\n", pid2);
  fprintf(stderr,"========================================\n");
  fprintf(stderr,"(SERVEUR) Demarrage de la boucle de routage des messages\n");
  fprintf(stderr,"(SERVEUR) Appuyez sur Ctrl+C pour arreter le serveur proprement\n\n");

  // Boucle principale : redirection des messages entre clients
  while(1) 
  {
    fprintf(stderr,"(SERVEUR) Attente d'une requete...\n");
    
    // Réception d'un message de type 1 (pour le serveur)
    if(msgrcv(idQ, &requete, sizeof(MESSAGE) - sizeof(long), 1, 0) == -1){
      perror("msgrcv");
      continue;
    }
    
    fprintf(stderr,"\n>>> MESSAGE RECU <<<\n");
    fprintf(stderr,"  Expediteur : %d\n", requete.expediteur);
    fprintf(stderr,"  Texte      : '%s'\n", requete.texte);
    
    // Ignorer les messages de connexion après l'initialisation
    if(strcmp(requete.texte, "CONNEXION") == 0){
      fprintf(stderr,"  [INFO] Message CONNEXION ignore (clients deja connectes)\n\n");
      continue;
    }
    
    // Vérifier que l'expéditeur est connu
    if(requete.expediteur != pid1 && requete.expediteur != pid2){
      fprintf(stderr,"  [ERREUR] Expediteur inconnu!\n");
      fprintf(stderr,"  Expected: %d ou %d, Got: %d\n\n", pid1, pid2, requete.expediteur);
      continue;
    }
    
    // Détermination du destinataire (l'autre client)
    if(requete.expediteur == pid1){
      destinataire = pid2;
      fprintf(stderr,"  Routage    : CLIENT1 (%d) -> CLIENT2 (%d)\n", pid1, pid2);
    }
    else{
      destinataire = pid1;
      fprintf(stderr,"  Routage    : CLIENT2 (%d) -> CLIENT1 (%d)\n", pid2, pid1);
    }
    
    // Préparation du message de réponse
    reponse.type = destinataire;
    reponse.expediteur = requete.expediteur;
    strncpy(reponse.texte, requete.texte, sizeof(reponse.texte) - 1);
    reponse.texte[sizeof(reponse.texte) - 1] = '\0';
    
    // Envoi du message au destinataire
    fprintf(stderr,"  Envoi msgsnd vers PID %d...\n", destinataire);
    if(msgsnd(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), 0) == -1){
      perror("  [ERREUR] msgsnd");
      continue;
    }
    fprintf(stderr,"  [OK] Message place dans la file\n");
    
    // Envoi du signal SIGUSR1 au destinataire pour le notifier
    fprintf(stderr,"  Envoi kill(SIGUSR1) vers PID %d...\n", destinataire);
    if(kill(destinataire, SIGUSR1) == -1){
      perror("  [ERREUR] kill");
      fprintf(stderr,"  Le processus %d existe-t-il encore?\n", destinataire);
      continue;
    }
    fprintf(stderr,"  [OK] Signal SIGUSR1 envoye\n");
    fprintf(stderr,">>> MESSAGE TRANSFERE AVEC SUCCES <<<\n\n");
  }
  
  return 0;
}
