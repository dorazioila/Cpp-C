#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include "LibSer.h"
#include "Requete.h"

#define RCVBUFSIZE 32   /* Size of receive buffer */

void HandleTCPClient(int clntSocket)
{
    int recvMsgSize;
    struct Requete UneRequete;

    /* Boucle de réception des messages */
    while ((recvMsgSize = recv(clntSocket, &UneRequete, sizeof(UneRequete), 0)) > 0)
    {
        printf("Bytes received: %d\n", recvMsgSize);
        printf("#%s\n", UneRequete.Chaine);

        /* Renvoi des données au client */
        int sentBytes = send(clntSocket, &UneRequete, recvMsgSize, 0);
        if (sentBytes != recvMsgSize)
            DieWithError("send() failed");

        printf("Bytes sent: %d\n", sentBytes);
    }

    /* Connexion fermée par le client */
    if (recvMsgSize < 0)
        DieWithError("recv() failed");

    printf("Bytes received: 0\n");
    printf("Connexion Closed\n");
    close(clntSocket);
}
