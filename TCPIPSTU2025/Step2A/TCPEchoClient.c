#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Requete.h"

void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock;                        
    struct sockaddr_in echoServAddr; 
    unsigned short echoServPort;     
    char *servIP;                    

    if (argc != 3)  /* Vérifie le nombre d’arguments */
    {
        fprintf(stderr, "Usage: %s <Server IP> <Echo Port>\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoServPort = atoi(argv[2]);

    /* Demande la référence à l’utilisateur */
    struct Requete UneRequete;
    int Numero; 
    printf("Entrez une référence: "); 
    scanf("%d", &Numero);

    memset(&UneRequete, 0, sizeof(struct Requete));
    UneRequete.Type = Question;
    UneRequete.Reference = Numero;

    /* Création de la socket TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);
    echoServAddr.sin_port = htons(echoServPort);

    /* Connexion au serveur */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    /* Envoi de la structure Requete au serveur */
    if (write(sock, &UneRequete, sizeof(struct Requete)) != sizeof(struct Requete))
        DieWithError("send() sent a different number of bytes than expected");

    /* Réception de la structure Requete depuis le serveur */
    if (read(sock, &UneRequete, sizeof(struct Requete)) <= 0)
        DieWithError("recv() failed or connection closed prematurely");

    /* Affiche la requête reçue */
    printf("Requête reçue du serveur :\n");
    AfficheRequete(UneRequete);

    close(sock);
    return 0;
}
