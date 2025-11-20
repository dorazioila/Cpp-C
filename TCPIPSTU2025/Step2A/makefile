all:	TCPEchoServer TCPEchoClient LibSerHV.o HandleTCPClient.o 
 
LibSerHV.o:	LibSerHV.c LibSerHV.h data.h 
	echo "Compilation de  LibSerHV.o" 
	gcc -c LibSerHV.c 
HandleTCPClient.o:	HandleTCPClient.c HandleTCPClient.h Requete.h 
	echo "Compilation de HandleTCPClient.o" 
	gcc -c HandleTCPClient.c 
TCPEchoServer:	TCPEchoServer.c HandleTCPClient.o LibSerHV.o 
	echo "Compilation de  TCPEchoServer" 
	gcc -o TCPEchoServer  TCPEchoServer.c  HandleTCPClient.o LibSerHV.o 
TCPEchoClient:	TCPEchoClient.c Requete.h 
	echo "Compilation de TCPEchoServer" 
	gcc -o TCPEchoClient TCPEchoClient.c 