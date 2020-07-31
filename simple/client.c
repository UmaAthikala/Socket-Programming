#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	
	int clientsocketfd=socket(AF_INET, SOCK_STREAM, 0);
	if(clientsocketfd<0)
	{
		printf("\n ERROR: socket creation failed");
		return 0;
	}
	
	struct sockaddr_in clientaddr;
	clientaddr.sin_family=AF_INET;
	clientaddr.sin_addr.s_addr=INADDR_ANY;
	clientaddr.sin_port=htons(8082);
	
	int sizeofaddr=sizeof(clientaddr);
	int connect_return=connect(clientsocketfd,(struct sockaddr*)&clientaddr,
sizeofaddr);
	if(connect_return<0)
	{
		printf("\n ERROR: connection failed");
		return 0;
	}

	send(clientsocketfd,"hello from client",strlen("hello from client"),0);
	printf("\nsent message to server");
	char buffer[1024];
	read(clientsocketfd,buffer, 1024);
	printf("\nCLIENT: received message - %s -",buffer);
	return 0;	
		
	
}
