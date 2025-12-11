#include "LibSerHV.h"
#include <fcntl.h>
#include <unistd.h>


void AProposServeurHV(char *Version,char *Nom1,char* Nom2)
{
 printf("Version : %s \n",Version ) ;
 printf("Nom1 : %s \n",Nom1 ) ;
 printf("Nom2 : %s \n",Nom2 ) ;

}

int RechercheHV(char* NomFichier, int Reference,struct VehiculeHV *UnRecord)
{
    int fd;
    int bytesRead;

    fd = open(NomFichier, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Erreur ouverture fichier %s\n",NomFichier);
        return -1;
    }

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

int AchatHV(char *NomFichier, int Reference, int Quantite)
{
    int fd = open(NomFichier, O_RDWR);
    struct VehiculeHV V;
    if (fd == -1) return -1;

    while (read(fd, &V, sizeof(V)) == sizeof(V)) {
        if (V.Reference == Reference && V.Supprime == 0) {
            if (V.Quantite < Quantite) {
                close(fd);
                return 0; // pas assez de stock
            }
            V.Quantite -= Quantite;
            lseek(fd, -sizeof(V), SEEK_CUR);
            write(fd, &V, sizeof(V));
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}

int LivraisonHV(char *NomFichier, int Reference, int Quantite)
{
    int fd = open(NomFichier, O_RDWR);
    struct VehiculeHV V;
    if (fd == -1) return -1;

    while (read(fd, &V, sizeof(V)) == sizeof(V)) {
        if (V.Reference == Reference && V.Supprime == 0) {
            V.Quantite += Quantite;
            lseek(fd, -sizeof(V), SEEK_CUR);
            write(fd, &V, sizeof(V));
            close(fd);
            return 1;
        }
    }
    close(fd);
    return 0;
}

void DieWithError(char*errorMessage){
    printf("erreur message : %s \n",errorMessage);
}


