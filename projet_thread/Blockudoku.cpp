#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include "GrilleSDL.h"
#include "Ressources.h"
#include <string.h>
#include <stdbool.h>

#define NB_LIGNES   9
#define NB_COLONNES 9

#define NB_CASES    4

#define VIDE        0
#define BRIQUE      1
#define DIAMANT     2

char* message = NULL; 
int tailleMessage; 
int indiceCourant; 
int score = 0;              
bool MAJScore = false;  
int combos = 0;
bool MAJCombos = false;
bool traitementEnCours = false;            
pthread_mutex_t mutexTraitement;          
pthread_cond_t condTraitement;            
pthread_mutex_t mutexScore; 
pthread_cond_t condScore; 
pthread_mutex_t mutexMessage;
pthread_mutex_t mutexCasesInserees;
pthread_cond_t condCasesInserees;
pthread_t tabThreadCase[9][9];
int lignesCompletes[9];
int nbLignesCompletes = 0;

int colonnesCompletes[9];
int nbColonnesCompletes = 0;

int carresComplets[9];
int nbCarresComplets = 0;

int nbAnalyses = 0;

pthread_mutex_t mutexAnalyse;
pthread_cond_t condAnalyse;
int tab[NB_LIGNES][NB_COLONNES] = {0};

typedef struct
{
  int ligne;
  int colonne;
} CASE;

typedef struct
{
  CASE cases[NB_CASES];
  int  nbCases;
  int  couleur;
} PIECE;

PIECE pieceEnCours;
CASE casesInserees[NB_CASES];
int nbCasesInserees = 0;

PIECE pieces[12] = { 0,0,0,1,1,0,1,1,4,0,       
                     0,0,1,0,2,0,2,1,4,0,       
                     0,1,1,1,2,0,2,1,4,0,       
                     0,0,0,1,1,1,1,2,4,0,       
                     0,1,0,2,1,0,1,1,4,0,       
                     0,0,0,1,0,2,1,1,4,0,       
                     0,0,0,1,0,2,0,3,4,0,       
                     0,0,0,1,0,2,0,0,3,0,       
                     0,1,1,0,1,1,0,0,3,0,       
                     0,0,1,0,1,1,0,0,3,0,       
                     0,0,0,1,0,0,0,0,2,0,       
                     0,0,0,0,0,0,0,0,1,0 };     



pthread_key_t clefCase;

void destructeurCase(void *ptr) {
    if (ptr != NULL) {
        free(ptr);
    }
}

void nettoyageMessage(void* arg) {
    pthread_mutex_lock(&mutexMessage);
    if (message != NULL) {
        free(message);
        message = NULL;
    }
    pthread_mutex_unlock(&mutexMessage);
}


void handlerSIGALRM(int sig);
void handlerSIGUSR1(int sig);

void DessinePiece(PIECE piece);
int  CompareCases(CASE case1,CASE case2);
void TriCases(CASE *vecteur,int indiceDebut,int indiceFin);
void* threadDefileMessage(void* arg);
void setMessage(const char *texte,bool signalOn);
void RotationPiece(PIECE *pPiece);

void* threadPiece(void* arg);
void* threadEvent(void* arg);
void* threadScore(void* arg);
void* threadCase(void* arg);
void* threadNettoyeur(void* arg);

int main(int argc,char* argv[])
{
  srand((unsigned)time(NULL));
  
  
  pthread_key_create(&clefCase, destructeurCase);
  

  struct sigaction action;
  action.sa_handler = handlerSIGALRM;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGALRM, &action, NULL);

  struct sigaction actionUSR1;
  actionUSR1.sa_handler = handlerSIGUSR1;
  sigemptyset(&actionUSR1.sa_mask);
  actionUSR1.sa_flags = 0;
  sigaction(SIGUSR1, &actionUSR1, NULL);
  
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGUSR1);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);
  
  pthread_mutex_init(&mutexCasesInserees, NULL);
  pthread_cond_init(&condCasesInserees, NULL);
  pthread_t thPiece;
  pthread_t thEvent;
  pthread_mutex_init(&mutexScore, NULL);
  pthread_cond_init(&condScore, NULL);
  pthread_mutex_init(&mutexTraitement, NULL);
  pthread_cond_init(&condTraitement, NULL);
  
  printf("(MAIN %p) Ouverture de la fenetre graphique\n",pthread_self()); fflush(stdout);
  if (OuvertureFenetreGraphique() < 0)
  {
    printf("Erreur de OuvrirGrilleSDL\n");
    fflush(stdout);
    exit(1);
  }
  
  DessineVoyant(8,10,VERT);
  pthread_create(&thEvent, NULL, threadEvent, NULL);
  pthread_create(&thPiece, NULL, threadPiece, NULL);
  
  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  pthread_sigmask(SIG_SETMASK, &mask, NULL);
  
  pthread_t thScore;
  pthread_create(&thScore, NULL, threadScore, NULL);
  pthread_t thDefile;
  pthread_mutex_init(&mutexMessage, NULL);
  pthread_mutex_lock(&mutexTraitement);
  traitementEnCours = false;
  pthread_mutex_unlock(&mutexTraitement);
  pthread_create(&thDefile, NULL, threadDefileMessage, NULL);
  setMessage("Bienvenue dans Blockudoku ",true);
  
  pthread_t thNettoyeur;
  pthread_create(&thNettoyeur, NULL, threadNettoyeur, NULL);

  pthread_mutex_init(&mutexAnalyse, NULL);
  pthread_cond_init(&condAnalyse, NULL);

  for(int L = 0; L < 9; L++)
  {
      for(int C = 0; C < 9; C++)
      {
          CASE* param = (CASE*) malloc(sizeof(CASE));
          param->ligne = L;
          param->colonne = C;

          pthread_create(&tabThreadCase[L][C], NULL, threadCase, param);
      }
  }

  
  

  
  pthread_join(thPiece, NULL);
  printf("(MAIN) Partie terminee : Fin du threadPiece detectee.\n");

  
  pthread_cancel(thEvent);
  pthread_join(thEvent, NULL); 
  
  
  
  pthread_cancel(thEvent);
  
  
  for(int L = 0; L < 9; L++) {
      for(int C = 0; C < 9; C++) {
          pthread_cancel(tabThreadCase[L][C]);
      }
  }
  for(int L = 0; L < 9; L++) {
      for(int C = 0; C < 9; C++) {
          pthread_join(tabThreadCase[L][C], NULL);
      }
  }

  
  printf("(MAIN %p) Attente du clic sur la croix...\n", pthread_self());
  while(1) {
      EVENT_GRILLE_SDL eventFin = ReadEvent();
      if(eventFin.type == CROIX) break;
  }

  
  pthread_cancel(thDefile);
  pthread_join(thDefile, NULL);

  
  
  printf("(MAIN %p) Fermeture de la fenetre graphique...",pthread_self()); fflush(stdout);
  FermetureFenetreGraphique();
  printf("OK\n");

  exit(0);
}

void DessinePiece(PIECE piece)
{
  int Lmin,Lmax,Cmin,Cmax;
  int largeur,hauteur,Lref,Cref;

  Lmin = piece.cases[0].ligne;
  Lmax = piece.cases[0].ligne;
  Cmin = piece.cases[0].colonne;
  Cmax = piece.cases[0].colonne;

  for (int i=1 ; i<=(piece.nbCases-1) ; i++)
  {
    if (piece.cases[i].ligne > Lmax) Lmax = piece.cases[i].ligne;
    if (piece.cases[i].ligne < Lmin) Lmin = piece.cases[i].ligne;
    if (piece.cases[i].colonne > Cmax) Cmax = piece.cases[i].colonne;
    if (piece.cases[i].colonne < Cmin) Cmin = piece.cases[i].colonne;
  }

  largeur = Cmax - Cmin + 1;
  hauteur = Lmax - Lmin + 1;

  switch(largeur)
  {
    case 1 : Cref = 15; break;
    case 2 : Cref = 15; break;
    case 3 : Cref = 14; break;
    case 4 : Cref = 14; break;  
  }

  switch(hauteur)
  {
    case 1 : Lref = 4; break;
    case 2 : Lref = 4; break;
    case 3 : Lref = 3; break;
    case 4 : Lref = 3; break;
  }

  for (int L=3 ; L<=6 ; L++) for (int C=14 ; C<=17 ; C++) EffaceCarre(L,C);
  for (int i=0 ; i<piece.nbCases ; i++) DessineDiamant(Lref + piece.cases[i].ligne,Cref + piece.cases[i].colonne,piece.couleur);
}


int CompareCases(CASE case1,CASE case2)
{
  if (case1.ligne < case2.ligne) return -1;
  if (case1.ligne > case2.ligne) return +1;
  if (case1.colonne < case2.colonne) return -1;
  if (case1.colonne > case2.colonne) return +1;
  return 0;
}

void TriCases(CASE *vecteur,int indiceDebut,int indiceFin)
{ 
  int  i,iMin;
  CASE tmp;

  if (indiceDebut >= indiceFin) return;
  
  iMin = indiceDebut;
  for (i=indiceDebut ; i<=indiceFin ; i++)
    if (CompareCases(vecteur[i],vecteur[iMin]) < 0) iMin = i;
  
  tmp = vecteur[indiceDebut];
  vecteur[indiceDebut] = vecteur[iMin];
  vecteur[iMin] = tmp;
  
  TriCases(vecteur,indiceDebut+1,indiceFin); 
}

void* threadDefileMessage(void* arg){
  sigset_t mask;
  sigemptyset(&mask);
  sigaddset(&mask, SIGALRM);
  pthread_sigmask(SIG_UNBLOCK, &mask, NULL); 

  
  pthread_cleanup_push(nettoyageMessage, NULL);
  

  struct timespec temps,reste;
  temps.tv_sec = 0;
  temps.tv_nsec = 400000000;
  
  while(1){
     pthread_mutex_lock(&mutexMessage);
     for(int i = 0; i < 17; i++){
      int indice = indiceCourant + i;
      if(indice < tailleMessage){
        DessineLettre(10,1 + i,message[indice]);
      }
      else{
        DessineLettre(10,1 + i,' ');
      }
     }
     indiceCourant++;
     if(indiceCourant >= tailleMessage){
      indiceCourant = 0;
     }
     pthread_mutex_unlock(&mutexMessage);
     
     nanosleep(&temps,&reste); 
  }
  
  pthread_cleanup_pop(0);
  return NULL;
}

void setMessage(const char *texte,bool signalOn){
  alarm(0);
  pthread_mutex_lock(&mutexMessage);
  free(message);
  message = (char*)malloc(strlen(texte) + 1); 
  strcpy(message, texte);                     
  tailleMessage = strlen(message);
  indiceCourant = 0;
  if(signalOn == true){
    alarm(10);
  }
  pthread_mutex_unlock(&mutexMessage);
}

void handlerSIGALRM(int sig){
  setMessage("jeux en cours", false);
}

void handlerSIGUSR1(int sig){

}

void RotationPiece(PIECE *pPiece)
{
    for(int i = 0 ; i < pPiece->nbCases ; i++)
    {
        int L = pPiece->cases[i].ligne;
        int C = pPiece->cases[i].colonne;

        pPiece->cases[i].ligne = -C;
        pPiece->cases[i].colonne = L;
    }
    
    int Lmin = pPiece->cases[0].ligne;
    int Cmin = pPiece->cases[0].colonne;

    for(int i = 1 ; i < pPiece->nbCases ; i++)
    {
        if(pPiece->cases[i].ligne < Lmin) Lmin = pPiece->cases[i].ligne;
        if(pPiece->cases[i].colonne < Cmin) Cmin = pPiece->cases[i].colonne;
    }
    
    for(int i = 0 ; i < pPiece->nbCases ; i++)
    {
        pPiece->cases[i].ligne -= Lmin;
        pPiece->cases[i].colonne -= Cmin;
    }
    TriCases(pPiece->cases,0,pPiece->nbCases-1);
}

void* threadPiece(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutexTraitement);
        while(traitementEnCours)
        {
            pthread_cond_wait(&condTraitement, &mutexTraitement);
        }
        pthread_mutex_unlock(&mutexTraitement);
        
        int couleurs[] = {ROUGE, VIOLET, VERT, ORANGE, BLEU, JAUNE};
        int indice = rand() % 12;

        pieceEnCours = pieces[indice];
        pieceEnCours.couleur = couleurs[rand() % 6];

        
        int nbRot = rand() % 4;
        for(int i = 0; i < nbRot; i++)
        {
            RotationPiece(&pieceEnCours);
        }

        DessinePiece(pieceEnCours);

        
        bool placeTrouvee = false;
        
        for (int L = 0; L < NB_LIGNES && !placeTrouvee; L++) {
            for (int C = 0; C < NB_COLONNES && !placeTrouvee; C++) {
                
                bool okPourPlacement = true;
                for (int i = 0; i < pieceEnCours.nbCases; i++) {
                    int ligneTest = L + pieceEnCours.cases[i].ligne;
                    int colTest = C + pieceEnCours.cases[i].colonne;
                    
                    if (ligneTest < 0 || ligneTest >= NB_LIGNES || 
                        colTest < 0 || colTest >= NB_COLONNES || 
                        tab[ligneTest][colTest] != VIDE) 
                    {
                        okPourPlacement = false;
                        break;
                    }
                }
                
                if (okPourPlacement) {
                    placeTrouvee = true; 
                }
            }
        }

        if (!placeTrouvee) {
            printf("(THREAD PIECE) Fin de partie detectee !\n");
            setMessage("GAME OVER !", false);
            pthread_exit(NULL); 
        }
        

        bool pieceValidee = false;

        while(!pieceValidee)
        {
            
            pthread_mutex_lock(&mutexCasesInserees);
            nbCasesInserees = 0;
            pthread_mutex_unlock(&mutexCasesInserees);

            
            pthread_mutex_lock(&mutexCasesInserees);
            while(nbCasesInserees < pieceEnCours.nbCases)
            {
                pthread_cond_wait(&condCasesInserees, &mutexCasesInserees);
            }
            pthread_mutex_unlock(&mutexCasesInserees);

            
            TriCases(casesInserees, 0, pieceEnCours.nbCases - 1);

            
            int Lmin = casesInserees[0].ligne;
            int Cmin = casesInserees[0].colonne;

            for(int i = 1; i < pieceEnCours.nbCases; i++)
            {
                if(casesInserees[i].ligne < Lmin) Lmin = casesInserees[i].ligne;
                if(casesInserees[i].colonne < Cmin) Cmin = casesInserees[i].colonne;
            }

            CASE temp[NB_CASES];

            for(int i = 0; i < pieceEnCours.nbCases; i++)
            {
                temp[i].ligne = casesInserees[i].ligne - Lmin;
                temp[i].colonne = casesInserees[i].colonne - Cmin;
            }

            
            bool ok = true;
            for(int i = 0; i < pieceEnCours.nbCases; i++)
            {
                if(temp[i].ligne != pieceEnCours.cases[i].ligne ||
                   temp[i].colonne != pieceEnCours.cases[i].colonne)
                {
                    ok = false;
                    break;
                }
            }
            if(ok)
            {
                for(int i = 0; i < pieceEnCours.nbCases; i++)
                {
                    int L = casesInserees[i].ligne;
                    int C = casesInserees[i].colonne;
                    tab[L][C] = BRIQUE;
                    DessineBrique(L, C, false);
                }

                
                pthread_mutex_lock(&mutexTraitement);
                traitementEnCours = true;
                DessineVoyant(8,10,BLEU);
                pthread_mutex_unlock(&mutexTraitement);

                
                for(int i = 0; i < pieceEnCours.nbCases; i++)
                {
                    int L = casesInserees[i].ligne;
                    int C = casesInserees[i].colonne;
                    pthread_kill(tabThreadCase[L][C], SIGUSR1);
                }

                
                pthread_mutex_lock(&mutexTraitement);
                while(traitementEnCours)
                {
                    pthread_cond_wait(&condTraitement, &mutexTraitement);
                }
                pthread_mutex_unlock(&mutexTraitement);

                
                pthread_mutex_lock(&mutexScore);
                score += pieceEnCours.nbCases;
                MAJScore = true;
                pthread_cond_signal(&condScore);
                pthread_mutex_unlock(&mutexScore);

                pieceValidee = true;
            }
            else
            {
                
                pthread_mutex_lock(&mutexCasesInserees);
                for(int i = 0; i < pieceEnCours.nbCases; i++)
                {
                    int L = casesInserees[i].ligne;
                    int C = casesInserees[i].colonne;
                    tab[L][C] = VIDE;       
                    EffaceCarre(L, C);      
                }
                pthread_mutex_unlock(&mutexCasesInserees);
            }
        }
    }

    return NULL;
}

void* threadEvent(void* arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    EVENT_GRILLE_SDL event;

    while(1)
    {
        event = ReadEvent();

        if(event.type == CROIX)
        {
            FermetureFenetreGraphique();
            exit(0);
        }

        if(event.type == CLIC_GAUCHE)
        {
            int L = event.ligne;
            int C = event.colonne;

            
            if(C >= NB_COLONNES)
            {
                pthread_mutex_lock(&mutexTraitement);

                DessineVoyant(8,10,ROUGE);

                struct timespec t = {0,400000000};
                nanosleep(&t,NULL);

                if(traitementEnCours)
                    DessineVoyant(8,10,BLEU);
                else
                    DessineVoyant(8,10,VERT);

                pthread_mutex_unlock(&mutexTraitement);
                continue;
            }

            pthread_mutex_lock(&mutexTraitement);

            
            if(traitementEnCours || tab[L][C] != VIDE)
            {
                DessineVoyant(8,10,ROUGE);

                struct timespec t = {0,400000000};
                nanosleep(&t,NULL);

                if(traitementEnCours)
                    DessineVoyant(8,10,BLEU);
                else
                    DessineVoyant(8,10,VERT);

                pthread_mutex_unlock(&mutexTraitement);
                continue;
            }

            pthread_mutex_unlock(&mutexTraitement);

            
            pthread_mutex_lock(&mutexCasesInserees);

            if(nbCasesInserees < pieceEnCours.nbCases)
            {
                tab[L][C] = DIAMANT;

                casesInserees[nbCasesInserees].ligne = L;
                casesInserees[nbCasesInserees].colonne = C;
                nbCasesInserees++;

                DessineDiamant(L, C, pieceEnCours.couleur);

                pthread_cond_signal(&condCasesInserees);
            }

            pthread_mutex_unlock(&mutexCasesInserees);
        }

        if(event.type == CLIC_DROIT)
        {
            pthread_mutex_lock(&mutexCasesInserees);

            for(int i = 0; i < nbCasesInserees; i++)
            {
                int L = casesInserees[i].ligne;
                int C = casesInserees[i].colonne;

                tab[L][C] = VIDE;
                EffaceCarre(L, C);
            }

            nbCasesInserees = 0;

            pthread_mutex_unlock(&mutexCasesInserees);
        }
    }

    return NULL;
}

void* threadScore(void* arg) {
    while (1) {
        pthread_mutex_lock(&mutexScore);

        while (!MAJScore && !MAJCombos) {
            pthread_cond_wait(&condScore, &mutexScore);
        }
        DessineChiffre(1, 14, (score / 1000) % 10);
        DessineChiffre(1, 15, (score / 100) % 10);
        DessineChiffre(1, 16, (score / 10) % 10);
        DessineChiffre(1, 17, score % 10);

        DessineChiffre(8, 14, (combos / 1000) % 10);
        DessineChiffre(8, 15, (combos / 100) % 10);
        DessineChiffre(8, 16, (combos / 10) % 10);
        DessineChiffre(8, 17, combos % 10);

        MAJScore = false;
        MAJCombos = false;

        pthread_mutex_unlock(&mutexScore);
    }
}

void* threadCase(void* arg)
{
    
    pthread_setspecific(clefCase, arg); 
    

    sigset_t mask;
    sigemptyset(&mask);  
    sigaddset(&mask, SIGUSR1);
    pthread_sigmask(SIG_UNBLOCK, &mask, NULL);

    CASE* maCase = (CASE*)arg;

    while(1)
    {
        pause(); 

        int L = maCase->ligne;
        int C = maCase->colonne;

        pthread_mutex_lock(&mutexAnalyse);
        
        bool complete = true;
        for(int i = 0; i < 9; i++)
        {
            if(tab[L][i] != BRIQUE)
                complete = false;
        }

        if(complete)
        {
            bool deja = false;
            for(int i=0;i<nbLignesCompletes;i++)
                if(lignesCompletes[i]==L) deja = true;

            if(!deja)
            {
                lignesCompletes[nbLignesCompletes++] = L;

                for(int i=0;i<9;i++)
                    DessineBrique(L,i,true);
            }
        }

        complete = true;
        for(int i = 0; i < 9; i++)
        {
            if(tab[i][C] != BRIQUE)
                complete = false;
        }

        if(complete)
        {
            bool deja = false;
            for(int i=0;i<nbColonnesCompletes;i++)
                if(colonnesCompletes[i]==C) deja = true;

            if(!deja)
            {
                colonnesCompletes[nbColonnesCompletes++] = C;

                for(int i=0;i<9;i++)
                    DessineBrique(i,C,true);
            }
        }
        int carre = (L/3)*3 + (C/3);

        int Lstart = (L/3)*3;
        int Cstart = (C/3)*3;

        complete = true;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(tab[Lstart+i][Cstart+j] != BRIQUE)
                    complete = false;
            }
        }

        if(complete)
        {
            bool deja = false;
            for(int i=0;i<nbCarresComplets;i++)
                if(carresComplets[i]==carre) deja = true;

            if(!deja)
            {
                carresComplets[nbCarresComplets++] = carre;

                for(int i=0;i<3;i++)
                    for(int j=0;j<3;j++)
                        DessineBrique(Lstart+i,Cstart+j,true);
            }
        }

        nbAnalyses++;

        pthread_cond_signal(&condAnalyse);
        pthread_mutex_unlock(&mutexAnalyse);
    }

    return NULL;
}

void* threadNettoyeur(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutexAnalyse);

        while(pieceEnCours.nbCases == 0 || nbAnalyses < pieceEnCours.nbCases)
        {
            pthread_cond_wait(&condAnalyse, &mutexAnalyse);
        }

        if(nbLignesCompletes == 0 && nbColonnesCompletes == 0 && nbCarresComplets == 0)
        {
            nbAnalyses = 0;
            pthread_mutex_unlock(&mutexAnalyse);

            
            pthread_mutex_lock(&mutexTraitement);
            traitementEnCours = false;
            DessineVoyant(8,10,VERT);
            pthread_cond_signal(&condTraitement);
            pthread_mutex_unlock(&mutexTraitement);

            continue;
        }

        pthread_mutex_unlock(&mutexAnalyse);

        struct timespec t;
        t.tv_sec = 2;
        t.tv_nsec = 0;
        pthread_mutex_lock(&mutexTraitement);
        DessineVoyant(8,10,BLEU);
        pthread_mutex_unlock(&mutexTraitement);
        nanosleep(&t, NULL);

        pthread_mutex_lock(&mutexAnalyse);

        int nbSuppr = 0;
        
        for(int i = 0; i < nbLignesCompletes; i++)
        {
            int L = lignesCompletes[i];
            for(int C = 0; C < 9; C++)
            {
                tab[L][C] = VIDE;
                EffaceCarre(L, C);
            }
            nbSuppr++;
        }
        
        for(int i = 0; i < nbColonnesCompletes; i++)
        {
            int C = colonnesCompletes[i];
            for(int L = 0; L < 9; L++)
            {
                tab[L][C] = VIDE;
                EffaceCarre(L, C);
            }
            nbSuppr++;
        }
        
        for(int i = 0; i < nbCarresComplets; i++)
        {
            int carre = carresComplets[i];
            int Lstart = (carre / 3) * 3;
            int Cstart = (carre % 3) * 3;

            for(int i=0;i<3;i++)
            {
                for(int j=0;j<3;j++)
                {
                    tab[Lstart+i][Cstart+j] = VIDE;
                    EffaceCarre(Lstart+i, Cstart+j);
                }
            }
            nbSuppr++;
        }

        nbLignesCompletes = 0;
        nbColonnesCompletes = 0;
        nbCarresComplets = 0;
        nbAnalyses = 0;

        pthread_mutex_unlock(&mutexAnalyse);
        
        const char* msg = NULL;

        if(nbSuppr == 1)
        {
            msg = "Simple Combo";
        }
        else if(nbSuppr == 2)
        {
            msg = "Double Combo";
        }
        else if(nbSuppr == 3)
        {
            msg = "Triple Combo";
        }
        else if(nbSuppr >= 4)
        {
            msg = "Quadruple Combo";
        }
        
        pthread_mutex_lock(&mutexScore);

        combos += nbSuppr;
        MAJCombos = true;

        if(nbSuppr == 1) score += 10;
        else if(nbSuppr == 2) score += 25;
        else if(nbSuppr == 3) score += 40;
        else if(nbSuppr >= 4) score += 55;

        MAJScore = true;

        pthread_cond_signal(&condScore);
        pthread_mutex_unlock(&mutexScore);
        
        if(msg != NULL)
        {
            setMessage(msg, true);
        }
        
        
      pthread_mutex_lock(&mutexTraitement);
      traitementEnCours = false;
      DessineVoyant(8,10,VERT);
      pthread_cond_signal(&condTraitement);
      pthread_mutex_unlock(&mutexTraitement);
    }
}