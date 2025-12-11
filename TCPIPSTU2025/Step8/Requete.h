#ifndef REQUETE_H
#define REQUETE_H

#include <stdio.h>

#define MAXCLIENT 60
#define MAXC 30

/* ===============================
   Codes de requêtes
   =============================== */
enum TypeRequete {
    Question     = 1,
    Achat        = 2,
    Livraison    = 3,
    Facturation  = 4,   /* <-- ajout Step8 */
    OK           = 10,
    Fail         = 11
};

/* ===============================
   Structure échangée Client ↔ Serveur
   =============================== */
struct Requete {
    enum TypeRequete Type;
    int NumeroFacture;        /* utilisé uniquement pour Facturation */
    int Reference;
    int Quantite;
    int Prix;

    char Constructeur[30];    /* pour réponse question */
    char Modele[30];
    char Client[30];          /* nom du client */
};

/* ===============================
   Fonction d'affichage
   =============================== */
static inline void AfficheRequete(struct Requete R) {
    fprintf(stderr, ">TypeRequete %d\n", R.Type);
    fprintf(stderr, ">NumeroFacture %d\n", R.NumeroFacture);
    fprintf(stderr, ">Reference %d\n", R.Reference);
    fprintf(stderr, ">Quantite %d\n", R.Quantite);
    fprintf(stderr, ">Prix %d\n", R.Prix);
    fprintf(stderr, ">Constructeur %s\n", R.Constructeur);
    fprintf(stderr, ">Modele %s\n", R.Modele);
    fprintf(stderr, ">Client %s\n\n", R.Client);
}

#endif
