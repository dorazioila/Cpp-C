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
    struct Requete reqR, reqE;
    struct VehiculeHV V;
    int rec, rc;

    rec = recv(clntSocket, &reqR, sizeof(reqR), 0);

    while (rec > 0) {

        printf("\n===== Requete reçue =====\n");
        AfficheRequete(reqR);

        memset(&reqE, 0, sizeof(reqE));

        switch (reqR.Type) {

            case Question:
                rc = RechercheHV("VehiculesHV", reqR.Reference, &V);

                if (rc == 1) {
                    reqE.Type = OK;
                    reqE.Reference = reqR.Reference;
                    strncpy(reqE.Constructeur, V.Constructeur, 30);
                    strncpy(reqE.Modele, V.Modele, 30);
                    reqE.Quantite = V.Quantite;
                } else {
                    reqE.Type = Fail;
                }
                break;

            case Achat:
                rc = AchatHV("VehiculesHV", reqR.Reference, reqR.Quantite);
                reqE.Type = (rc == 1 ? OK : Fail);
                break;

            case Livraison:
                rc = LivraisonHV("VehiculesHV", reqR.Reference, reqR.Quantite);
                reqE.Type = (rc == 1 ? OK : Fail);
                break;

            default:
                printf("Code requête invalide : %d\n", reqR.Type);
                reqE.Type = Fail;
                break;
        }

        /* Envoi réponse */
        send(clntSocket, &reqE, sizeof(reqE), 0);

        /* Attente requête suivante */
        rec = recv(clntSocket, &reqR, sizeof(reqR), 0);
    }

    printf("Fermeture connexion client.\n");
    close(clntSocket);
}
