#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

#include "LibSer.h"
#include "HandleTCPClient.h"

#define MAXPENDING 5

int main(int argc, char *argv[])
{
    int servSock, clntSock;
    struct sockaddr_in servAddr, cliAddr;
    socklen_t cliLen = sizeof(cliAddr);
    unsigned short servPort;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    char *ip = argv[1];
    servPort = atoi(argv[2]);

    /* socket */
    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servSock < 0)
        DieWithError("socket() failed");

    memset(&servAddr, 0, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(servPort);

    if (bind(servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
        DieWithError("bind() failed");

    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    printf("Serveur en écoute sur %s:%d\n", ip, servPort);

    while (1) {
        cliLen = sizeof(cliAddr);
        clntSock = accept(servSock, (struct sockaddr *)&cliAddr, &cliLen);

        /* ===== Ajout Step4 : Infos client ===== */
        struct sockaddr_storage adrClient;
        socklen_t adrLen = sizeof(adrClient);
        char host[NI_MAXHOST];
        char port[NI_MAXSERV];

        getpeername(clntSock, (struct sockaddr*)&adrClient, &adrLen);

        getnameinfo((struct sockaddr*)&adrClient, adrLen,
                    host, sizeof(host),
                    port, sizeof(port),
                    NI_NUMERICHOST | NI_NUMERICSERV);

        printf("Client connecté --> IP: %s  Port: %s\n", host, port);

        HandleTCPClient(clntSock);
    }
}
