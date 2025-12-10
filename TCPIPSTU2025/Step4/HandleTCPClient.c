#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "LibSer.h"
#include "Requete.h"
#include "data.h"
#include "LibSerHV.h"

void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;
    int bytesSent;
    struct Requete uneRequeteR;
    struct Requete uneRequeteE;
    struct VehiculeHV UnRecord;
    int rc;

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, &uneRequeteR, sizeof(struct Requete), 0)) < 0)
        DieWithError("recv() failed");

    while (recvMsgSize > 0)
    {
        printf("Bytes received:%d\n", recvMsgSize);
        
        /* Afficher la requête reçue */
        AfficheRequete(uneRequeteR);

        /* Rechercher le véhicule dans le fichier */
        rc = RechercheHV("VehiculesHV", uneRequeteR.Reference, &UnRecord);

        /* Initialiser la réponse */
        memset(&uneRequeteE, 0, sizeof(struct Requete));
        
        /* Préparer la réponse selon le résultat de la recherche */
        if (rc == 1) { // Véhicule trouvé
            strncpy(uneRequeteE.Constructeur, UnRecord.Constructeur, sizeof(uneRequeteE.Constructeur));
            strncpy(uneRequeteE.Modele, UnRecord.Modele, sizeof(uneRequeteE.Modele));
            uneRequeteE.Quantite = UnRecord.Quantite;
            uneRequeteE.Type = OK;
            uneRequeteE.Reference = uneRequeteR.Reference;
            uneRequeteE.NumeroFacture = uneRequeteR.NumeroFacture;
            uneRequeteE.Prix = 0;
        } else { // Véhicule non trouvé
            uneRequeteE = uneRequeteR;
            uneRequeteE.Type = Fail;
        }

        /* Envoyer la réponse au client */
        bytesSent = write(clntSocket, &uneRequeteE, sizeof(struct Requete));
        if (bytesSent != sizeof(struct Requete))
            DieWithError("send() failed");
        
        printf("bytes ecrits %d\n", bytesSent);

        /* Voir s'il y a plus de données à recevoir */
        if ((recvMsgSize = recv(clntSocket, &uneRequeteR, sizeof(struct Requete), 0)) < 0)
            DieWithError("recv() failed");
    }

    printf("Connexion Closed\n");
    close(clntSocket);
}
