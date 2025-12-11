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
    struct sockaddr_storage cliAddr;
    socklen_t cliLen = sizeof(cliAddr);
    unsigned short servPort;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <HostName/IP> <Port>\n", argv[0]);
        exit(1);
    }

    char *hostName = argv[1];
    servPort = atoi(argv[2]);

    /* ===============================
       Résolution du serveur avec getaddrinfo()
    ================================== */
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_INET;        // IPv4
    hints.ai_socktype = SOCK_STREAM;    // TCP
    hints.ai_flags    = AI_PASSIVE;     // Pour bind()

    if (getaddrinfo(hostName, argv[2], &hints, &res) != 0)
        DieWithError("getaddrinfo() failed");

    printf("Adresse résolue : %s\n",
           inet_ntoa(((struct sockaddr_in*)res->ai_addr)->sin_addr));
    
    /* Création socket */
    servSock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (servSock < 0)
        DieWithError("socket() failed");

    /* Bind */
    if (bind(servSock, res->ai_addr, res->ai_addrlen) < 0)
        DieWithError("bind() failed");

    freeaddrinfo(res);

    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");

    printf("Serveur en écoute...\n");

    /* Boucle MultiClients */
    while (1) {
        cliLen = sizeof(cliAddr);
        clntSock = accept(servSock, (struct sockaddr *)&cliAddr, &cliLen);

        char host[NI_MAXHOST], port[NI_MAXSERV];
        getnameinfo((struct sockaddr*)&cliAddr, cliLen,
                host, sizeof(host),
                port, sizeof(port),
                NI_NUMERICHOST | NI_NUMERICSERV);

        printf("Client connecté : %s:%s\n", host, port);

        HandleTCPClient(clntSock);
    }
}
