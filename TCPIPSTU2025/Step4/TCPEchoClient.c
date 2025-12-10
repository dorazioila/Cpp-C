#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "Requete.h"
#include "LibSer.h"

int main(int argc, char *argv[])
{
    int sock;                        
    struct sockaddr_in echoServAddr; 
    unsigned short echoServPort;     
    char *servIP;                    
    int bytesSent, bytesReceived;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <Server IP> <Echo Port>\n", argv[0]);
        exit(1);
    }

    servIP = argv[1];
    echoServPort = atoi(argv[2]);

    /* Demande la référence à l'utilisateur */
    struct Requete UneRequete;
    int Numero;

    printf("Entrez une référence:");
    scanf("%d", &Numero);

    /* Initialiser la requête */
    memset(&UneRequete, 0, sizeof(struct Requete));
    UneRequete.Type = Question;
    UneRequete.Reference = Numero;
    UneRequete.NumeroFacture = 0;
    UneRequete.Quantite = 0;
    UneRequete.Prix = 0;

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
    bytesSent = write(sock, &UneRequete, sizeof(struct Requete));
    if (bytesSent != sizeof(struct Requete))
        DieWithError("send() sent a different number of bytes than expected");
    
    printf("Bytes send:%d\n", bytesSent);

    /* Réception de la structure Requete depuis le serveur */
    bytesReceived = read(sock, &UneRequete, sizeof(struct Requete));
    if (bytesReceived <= 0)
        DieWithError("recv() failed or connection closed prematurely");

    printf("Bytes received:%d\n", bytesReceived);

    /* Affiche la requête reçue */
    AfficheRequete(UneRequete);

    /* Affichage final formaté */
    printf("Constructeur , Modele:%s %s\n", UneRequete.Constructeur, UneRequete.Modele);

    close(sock);
    return 0;
}
