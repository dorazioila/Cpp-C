#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

#define RCVBUFSIZE 32

void HandleTCPClient(int clntSocket)
{
    char echoBuffer[RCVBUFSIZE];
    int recvMsgSize;

    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
    {
        fprintf(stderr, "recv() failed\n");
    }

    while (recvMsgSize > 0)
    {
        if (send(clntSocket, echoBuffer, recvMsgSize, 0) != recvMsgSize)
        {
            fprintf(stderr, "send() failed\n");
        }

        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        {
            fprintf(stderr, "recv() failed\n");
        }
    }

    close(clntSocket);
}
