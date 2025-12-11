#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#include "Requete.h"
#include "LibSer.h"

void Menu() {
    printf("\n===== MENU CLIENT =====\n");
    printf("1 - Question\n");
    printf("2 - Achat\n");
    printf("3 - Livraison\n");
    printf("4 - Quitter\n");
    printf("Votre choix : ");
}

int main(int argc, char *argv[])
{
    int sock, choice;
    unsigned short port;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <HostName/IP> <Port>\n", argv[0]);
        exit(1);
    }

    char *hostName = argv[1];
    port = atoi(argv[2]);

    /* ===============================
       Résolution du serveur avec getaddrinfo()
    ================================== */
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostName, argv[2], &hints, &res) != 0)
        DieWithError("getaddrinfo() failed");

    printf("Résolu vers : %s\n",
           inet_ntoa(((struct sockaddr_in*)res->ai_addr)->sin_addr));

    /* Socket */
    sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sock < 0)
        DieWithError("socket() failed");

    /* Connexion */
    if (connect(sock, res->ai_addr, res->ai_addrlen) < 0)
        DieWithError("connect() failed");

    freeaddrinfo(res);

    /* Boucle menu */
    while (1) {
        struct Requete req, rep;
        memset(&req, 0, sizeof(req));

        Menu();
        scanf("%d", &choice);

        if (choice == 4) {
            printf("Déconnexion...\n");
            break;
        }

        switch (choice) {
            case 1:
                req.Type = Question;
                printf("Référence : ");
                scanf("%d", &req.Reference);
                break;

            case 2:
                req.Type = Achat;
                printf("Référence : ");
                scanf("%d", &req.Reference);
                printf("Quantité : ");
                scanf("%d", &req.Quantite);
                printf("Client : ");
                scanf("%s", req.Client);
                break;

            case 3:
                req.Type = Livraison;
                printf("Référence : ");
                scanf("%d", &req.Reference);
                printf("Quantité : ");
                scanf("%d", &req.Quantite);
                break;

            default:
                printf("Choix invalide.\n");
                continue;
        }

        write(sock, &req, sizeof(req));
        read(sock, &rep, sizeof(rep));

        printf("\n===== REPONSE SERVEUR =====\n");
        AfficheRequete(rep);
    }

    close(sock);
    return 0;
}
