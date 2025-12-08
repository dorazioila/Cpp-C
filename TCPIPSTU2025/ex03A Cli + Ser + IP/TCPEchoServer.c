#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAXPENDING 5

#include "LibSer.h"
#include "HandleTCPClient.h"

int main(int argc, char *argv[])
{
    int servSock, clntSock;
    struct sockaddr_in echoServAddr, echoClntAddr;
    unsigned short echoServPort;
    unsigned int clntLen;

    /* Vérification des arguments */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    char *ip = argv[1];                 // Adresse IP passée en paramètre
    echoServPort = atoi(argv[2]);       // Port passé en paramètre

    /* Création du socket */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
    printf("socket() Ok\n");

    /* Initialisation de la structure de l'adresse serveur */
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(ip);  // On utilise le paramètre IP
    echoServAddr.sin_port = htons(echoServPort);   // On utilise le paramètre port

    /* Binding du socket à l'adresse IP et au port */
    if (bind(servSock, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");
    printf("bind() Ok\n");

    /* Écoute des connexions entrantes */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    printf("listen() Ok\n");

    /* Boucle principale pour accepter les clients */
    for (;;) {
        clntLen = sizeof(echoClntAddr);
        if ((clntSock = accept(servSock, (struct sockaddr *)&echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed");
        printf("accept() Ok\n");

        printf("### Le Serveur\n");
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        /* Gestion du client */
        HandleTCPClient(clntSock);
    }

    return 0;
}
