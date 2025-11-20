#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAXPENDING 5

#include "LibSer.h"
#include "HandleTCPClient.h"

int main(int argc, char *argv[])
{
    int servSock;
    int clntSock;
    struct sockaddr_in echoServAddr;
    struct sockaddr_in echoClntAddr;
    unsigned short echoServPort;
    char *servIP;                      // NOUVEAU : variable pour l'IP
    unsigned int clntLen;

    if (argc != 3)                     // MODIFIÉ : 3 arguments au lieu de 2
    {
        fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];                  // NOUVEAU : récupération de l'IP
    echoServPort = atoi(argv[2]);      // MODIFIÉ : le port est maintenant argv[2]

    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
    else
       printf("socket() Ok\n");

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);  // MODIFIÉ : utilisation de l'IP spécifiée
    echoServAddr.sin_port = htons(echoServPort);

    if (bind(servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("bind() failed");
    else
       printf("bind() Ok\n");

    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    else
       printf("listen() Ok\n");

    for (;;)
    {
        clntLen = sizeof(echoClntAddr);

        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed");
        else
           printf("accept() Ok\n");

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        HandleTCPClient(clntSock);
    }
}
