all:	admin TCPEchoServer TCPEchoClient HandleTCPClient.o LibSerHV.o 
 
admin:	data.h admin.c LibSerHV.o   
	echo "Compilation de admin" 
	cc -o admin admin.c  LibSerHV.o 
LibSerHV.o:	LibSerHV.c LibSerHV.h data.h  
	echo "compilation de LibSerHV" 
	cc -c LibSerHV.c 
TCPEchoServer:	TCPEchoServer.c HandleTCPClient.o LibSerHV.o 
	echo "Compilation de  TCPEchoServer" 
	gcc -o TCPEchoServer  TCPEchoServer.c  HandleTCPClient.o  LibSerHV.o 
TCPEchoClient:	TCPEchoClient.c LibSerHV.o
	gcc -o TCPEchoClient TCPEchoClient.c LibSerHV.o
HandleTCPClient.o:	HandleTCPClient.c HandleTCPClient.h Requete.h data.h LibSerHV.h
	echo "Compilation de HandleTCPClient.o"
	gcc -c HandleTCPClient.c
