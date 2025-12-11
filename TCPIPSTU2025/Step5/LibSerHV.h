#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

#ifndef LIBSERHV_H
#define LIBSERHV_H

void AProposServeurHV(char *Version,char *Nom1,char* Nom2);
int RechercheHV(char* NomFichier, int Reference, struct VehiculeHV *UnRecord);
int AchatHV(char *NomFichier, int Reference, int Quantite);
int LivraisonHV(char *NomFichier, int Reference, int Quantite);
void DieWithError(char* errorMessage);

#endif