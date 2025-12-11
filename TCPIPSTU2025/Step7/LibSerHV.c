#include "LibSerHV.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>   // pour stat()

void AProposServeurHV(char *Version,char *Nom1,char* Nom2)
{
    printf("Version : %s \n",Version);
    printf("Nom1 : %s \n",Nom1);
    printf("Nom2 : %s \n",Nom2);
}

int RechercheHV(char* NomFichier, int Reference,struct VehiculeHV *UnRecord)
{
    int fd, bytesRead;
    fd = open(NomFichier, O_RDONLY);
    if(fd == -1) return -1;

    bytesRead = read(fd, UnRecord, sizeof(struct VehiculeHV));
    while(bytesRead == sizeof(struct VehiculeHV))
    {
        if(UnRecord->Reference == Reference && UnRecord->Supprime == 0)
        {
            close(fd);
            return 1;
        }
        bytesRead = read(fd, UnRecord, sizeof(struct VehiculeHV));
    }
    close(fd);
    return 0;
}

void DieWithError(char* errorMessage){
    printf("erreur message : %s \n", errorMessage);
}

// 🔹 ReservationHV
int ReservationHV(char* NomFichier, int Reference, int Quantite)
{
    int fd;
    struct VehiculeHV Record;
    int bytesRead;
    off_t pos;

    fd = open(NomFichier, O_RDWR);
    if(fd == -1) return -1;

    bytesRead = read(fd, &Record, sizeof(struct VehiculeHV));
    while(bytesRead == sizeof(struct VehiculeHV))
    {
        if(Record.Reference == Reference && Record.Supprime == 0)
        {
            if(Record.Quantite < Quantite)
            {
                close(fd);
                return 0; // stock insuffisant
            }
            Record.Quantite -= Quantite;
            pos = lseek(fd, -sizeof(struct VehiculeHV), SEEK_CUR);
            write(fd, &Record, sizeof(struct VehiculeHV));
            close(fd);
            return 1; // OK
        }
        bytesRead = read(fd, &Record, sizeof(struct VehiculeHV));
    }
    close(fd);
    return 0; // référence non trouvée
}

// 🔹 FacturationHV
int FacturationHV(char NomFichier[80], char NomClient[60], time_t Date, int Quantite, int Reference)
{
    int fd;
    struct FactureHV Facture;
    struct stat st;
    long nbrFactures;

    fd = open(NomFichier, O_WRONLY | O_APPEND | O_CREAT, 0666);
    if(fd == -1) return -1;

    if(stat(NomFichier, &st) == 0)
        nbrFactures = st.st_size / sizeof(struct FactureHV);
    else
        nbrFactures = 0;

    Facture.NumeroFacturation = nbrFactures + 1;
    strcpy(Facture.Acheteur, NomClient);
    Facture.DateFacturation = Date;
    Facture.Quantite = Quantite;
    Facture.Reference = Reference;

    write(fd, &Facture, sizeof(struct FactureHV));
    close(fd);
    return 1;
}
