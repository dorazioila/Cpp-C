
enum TypeRequete { 
Question = 1 , 
Achat  = 2 , 
Livraison= 3 , 
OK  = 4, 
Fail = 5  
} ; 
struct Requete { 
  enum TypeRequete Type ; 
  int Numero ; // Contient le numéro de la requete  
  int NumeroFacture ; 
  time_t Date ;  
  int Reference ; // la référence du Véhicule 
  int Quantite ; ; 
  int Prix ; 
  char Constructeur[30] ; 
  char Modele[30] ; 
  char NomClient[80] ;  
} ;  
#include <stdio.h>  
void AfficheRequete( struct Requete R ) { 
  fprintf(stderr,">TypeRequete %d \n", R.Type ) ; 
  fprintf(stderr,">Reference %d \n", R.Numero ) ; 
  fprintf(stderr,">NumeroFacture %d \n", R.NumeroFacture ) ; 
  fprintf(stderr,">Date %ld \n", R.Date ) ; 
  fprintf(stderr,">Reference %d \n", R.Reference ) ; 
  fprintf(stderr,">Places %d \n", R.Quantite ) ; 
  fprintf(stderr,">Prix %d \n", R.Prix ) ; 
  fprintf(stderr,">Constructeur %s \n", R.Constructeur ) ; 
  fprintf(stderr,">Modele %s \n", R.Modele ) ; 
  fprintf(stderr,">Client %s \n\n", R.NomClient ) ; 

  return ; 
}