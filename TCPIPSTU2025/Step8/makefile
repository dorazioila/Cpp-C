all: admin TCPEchoServer TCPEchoClient HandleTCPClient.o LibSerHV.o LibSerFacture.o
 
admin: data.h admin.c LibSerHV.o   
	echo "Compilation de admin" 
	cc -o admin admin.c LibSerHV.o 

LibSerHV.o: LibSerHV.c LibSerHV.h data.h  
	echo "compilation de LibSerHV" 
	cc -c LibSerHV.c 

LibSerFacture.o: LibSerFacture.c LibSerHV.h data.h
	echo "Compilation de LibSerFacture"
	cc -c LibSerFacture.c

TCPEchoServer: TCPEchoServer.c HandleTCPClient.o LibSerHV.o LibSerFacture.o
	echo "Compilation de  TCPEchoServer" 
	gcc -o TCPEchoServer TCPEchoServer.c HandleTCPClient.o LibSerHV.o LibSerFacture.o

TCPEchoClient: TCPEchoClient.c LibSerHV.o
	gcc -o TCPEchoClient TCPEchoClient.c LibSerHV.o

HandleTCPClient.o: HandleTCPClient.c HandleTCPClient.h Requete.h data.h LibSerHV.h
	echo "Compilation de HandleTCPClient.o"
	gcc -c HandleTCPClient.c
