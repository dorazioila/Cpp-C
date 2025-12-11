#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "Requete.h"
#include "LibSer.h"

void Menu() {
    printf("\n===== MENU CLIENT =====\n");
    printf("1 - Question (Infos véhicule)\n");
    printf("2 - Achat\n");
    printf("3 - Livraison\n");
    printf("4 - Quitter\n");
    printf("5 - Facturation\n");
    printf("Votre choix : ");
}

int main(int argc, char *argv[])
{
    int sock;
    struct sockaddr_in echoServAddr;
    unsigned short echoServPort;
    char *servIP;
    int choice;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoServPort = atoi(argv[2]);

    /* Création socket */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    /* Connexion */
    if (connect(sock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    while (1) {
        struct Requete req;
        struct Requete rep;
        memset(&req, 0, sizeof(req));

        Menu();
        if (scanf("%d", &choice) != 1) {
            fprintf(stderr, "Lecture choix impossible\n");
            break;
        }

        if (choice == 4) {
            printf("Déconnexion...\n");
            break;
        }

        switch (choice) {

            case 1:   /* QUESTION */
                req.Type = Question;
                printf("Référence du véhicule : ");
                scanf("%d", &req.Reference);
                break;

            case 2:   /* ACHAT */
                req.Type = Achat;
                printf("Référence du véhicule : ");
                scanf("%d", &req.Reference);
                printf("Quantité achetée : ");
                scanf("%d", &req.Quantite);
                printf("Nom client : ");
                scanf("%s", req.Client);
                break;

            case 3:   /* LIVRAISON */
                req.Type = Livraison;
                printf("Référence du véhicule : ");
                scanf("%d", &req.Reference);
                printf("Quantité livrée : ");
                scanf("%d", &req.Quantite);
                break;

            case 5:   /* FACTURATION */
                req.Type = Facturation;
                printf("Nom client : ");
                /* lecture simple (pas d'espace) */
                scanf("%s", req.Client);
                printf("Référence souhaitée : ");
                scanf("%d", &req.Reference);
                printf("Quantité commandée : ");
                scanf("%d", &req.Quantite);
                break;

            default:
                printf("Choix invalide.\n");
                continue;
        }

        /* Envoi de la requête */
        if (write(sock, &req, sizeof(req)) != sizeof(req))
            DieWithError("send() error");

        /* Réception réponse */
        int rec = read(sock, &rep, sizeof(rep));
        if (rec <= 0)
            DieWithError("recv() failed");

        printf("\n===== REPONSE SERVEUR =====\n");
        AfficheRequete(rep);

        if (rep.Type == Fail) {
            printf(">>> ECHEC de l'opération.\n");
        } else if (req.Type == Facturation && rep.Type == OK) {
            printf("Votre numéro de facture est : %d\n", rep.NumeroFacture);

        }
    }

    close(sock);
    return 0;
}
