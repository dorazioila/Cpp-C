#include "windowclient.h"
#include "ui_windowclient.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

extern WindowClient *w;

#include "protocole.h" // contient la cle et la structure d'un message

extern char nomClient[40];
int idQ; // identifiant de la file de message

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Handler de signal (Étape 4) ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void handlerSIGUSR1(int sig)
{
  MESSAGE reponse;
  
  fprintf(stderr,"(CLIENT %d) Reception du signal SIGUSR1\n", getpid());
  
  // 1. Lecture du message destiné au client (type = son PID)
  if(msgrcv(idQ, &reponse, sizeof(MESSAGE) - sizeof(long), getpid(), IPC_NOWAIT) == -1){ // no wait = pour ne pas attendre du message client 
    perror("msgrcv dans handler");
    return;
  }
  
  fprintf(stderr,"(CLIENT %d) Message recu de %d : %s\n", 
          getpid(), reponse.expediteur, reponse.texte);
  
  // 2. Affichage de la réponse dans la fenêtre
  w->setRecu(reponse.texte);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Constructeur et Destructeur ////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
WindowClient::WindowClient(QWidget *parent):QMainWindow(parent),ui(new Ui::WindowClient)
{
  ui->setupUi(this);
  setWindowTitle(nomClient);

  // Recuperation de l'identifiant de la file de messages
  fprintf(stderr,"(CLIENT %s %d) Recuperation de l'id de la file de messages\n",
          nomClient, getpid());
  idQ = msgget(CLE, 0666);
  if(idQ == -1){
    perror("msgget");
    exit(1);
  }

  // Armement du signal SIGUSR1 (Étape 4)
  fprintf(stderr,"(CLIENT %s %d) Armement du signal SIGUSR1\n", nomClient, getpid());
  struct sigaction sa;
  sa.sa_handler = handlerSIGUSR1;  // Pointeur vers le handler
  sigemptyset(&sa.sa_mask);        // Aucun signal bloqué pendant l'exécution
  sa.sa_flags = 0;                 // Pas d'options spéciales
  
  if(sigaction(SIGUSR1, &sa, NULL) == -1){
    perror("sigaction");
    exit(1);
  }
  fprintf(stderr,"(CLIENT %s %d) Signal SIGUSR1 arme avec succes\n", nomClient, getpid());

  // Envoi d'une requete d'identification (Étape 5)
  fprintf(stderr,"(CLIENT %s %d) Envoi d'une requete d'identification\n",
          nomClient, getpid());
  MESSAGE msg;
  msg.type = 1;  // Type pour le serveur
  msg.expediteur = getpid();  // PID du client
  sprintf(msg.texte, "CONNEXION");
  
  if(msgsnd(idQ, &msg, sizeof(MESSAGE) - sizeof(long), 0) == -1){
    perror("msgsnd identification");
    exit(1);
  }
  fprintf(stderr,"(CLIENT %s %d) Identification envoyee au serveur\n", nomClient, getpid());
}

WindowClient::~WindowClient()
{
  delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::setRecu(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditRecu->clear();
    return;
  }
  ui->lineEditRecu->setText(Text);
}

void WindowClient::setAEnvoyer(const char* Text)
{
  if (strlen(Text) == 0 )
  {
    ui->lineEditEnvoyer->clear();
    return;
  }
  ui->lineEditEnvoyer->setText(Text);
}

const char* WindowClient::getAEnvoyer()
{
  if (ui->lineEditEnvoyer->text().size())
  { 
    strcpy(aEnvoyer,ui->lineEditEnvoyer->text().toStdString().c_str());
    return aEnvoyer;
  }
  return NULL;
}

const char* WindowClient::getRecu()
{
  if (ui->lineEditRecu->text().size())
  { 
    strcpy(recu,ui->lineEditRecu->text().toStdString().c_str());
    return recu;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons (Étape 5 : ASYNCHRONE entre 2 clients) /////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WindowClient::on_pushButtonEnvoyer_clicked()
{
  fprintf(stderr,"(CLIENT %d) Clic sur le bouton Envoyer\n", getpid());
  MESSAGE m;

  // Récupération du texte à envoyer
  const char* txt = getAEnvoyer();
  if(txt == nullptr || strlen(txt) == 0){
    fprintf(stderr,"(CLIENT %d) Aucun texte a envoyer\n", getpid());
    return;
  }
  
  // Préparation du message
  m.type = 1;  // Type 1 = convention pour le serveur
  m.expediteur = getpid();  // PID du client expéditeur
  strncpy(m.texte, txt, sizeof(m.texte) - 1);
  m.texte[sizeof(m.texte) - 1] = '\0';
  
  // Envoi ASYNCHRONE du message au serveur
  fprintf(stderr,"(CLIENT %d) Envoi du message au serveur : %s\n", getpid(), m.texte);
  if(msgsnd(idQ, &m, sizeof(MESSAGE) - sizeof(long), 0) == -1){
    perror("msgsnd");
    return;
  }
  
  fprintf(stderr,"(CLIENT %d) Message envoye (sera redirige vers l'autre client)\n", getpid());
  
  // Effacer la zone d'envoi
  setAEnvoyer("");
  
  
}

void WindowClient::on_pushButtonQuitter_clicked()
{
  fprintf(stderr,"(CLIENT %d) Clic sur le bouton Quitter\n", getpid());
  exit(1);
}
