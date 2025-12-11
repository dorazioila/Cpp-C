#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include "data.h"

int FacturationHV(char *NomFichier, char *client, int reference, int quantite)
{
    struct FactureHV facture;
    int fd;

    // Génération du numéro de facture
    srand(time(NULL));
    int numFacture = rand() % 100000 + 1;

    facture.NumeroFacturation = numFacture;
    strncpy(facture.Acheteur, client, 40);
    facture.Acheteur[39] = '\0'; // sécurité
    facture.DateFacturation = time(NULL);
    facture.Reference = reference;
    facture.Quantite = quantite;

    // Ouverture du fichier facture
    fd = open(NomFichier, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("Erreur ouverture fichier FactureHV");
        return -1;
    }

    // Écriture de la facture dans le fichier
    if (write(fd, &facture, sizeof(facture)) != sizeof(facture))
    {
        perror("Erreur écriture facture");
        close(fd);
        return -1;
    }

    close(fd);
    return numFacture;
}
