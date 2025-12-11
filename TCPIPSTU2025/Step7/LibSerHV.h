#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

#ifndef LIBSERHV_H
#define LIBSERHV_H

// fonctions déjà présentes
void AProposServeurHV(char *Version,char *Nom1,char* Nom2);
int RechercheHV(char* NomFichier, int Reference, struct VehiculeHV *UnRecord);
void DieWithError(char* errorMessage);

//  Déclarations à ajouter pour supprimer les warnings
int ReservationHV(char* NomFichier, int Reference, int Quantite);
int FacturationHV(char NomFichier[80], char NomClient[60], time_t Date, int Quantite, int Reference);

#endif


