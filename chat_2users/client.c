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
	clientaddr.sin_port=htons(8088);
	
	int sizeofaddr=sizeof(clientaddr);
	int connect_return=connect(clientsocketfd,(struct sockaddr*)&clientaddr,
sizeofaddr);
	if(connect_return<0)
	{
		printf("\n ERROR: connection failed");
		return 0;
	}

	char msgs[1024];
	char endstr[4];
	strcpy(endstr,"end");
	do{
	
	fgets(msgs,1024,stdin);
	
	//printf("\nlength is : %d , compare: %d",strlen(msgs),strcmp(msgs,endstr));
	send(clientsocketfd,msgs,strlen(msgs),0);
	printf("\t\t\t..............sent");
	char buffer[1024];
	read(clientsocketfd,buffer, 1024);
	printf("\nCLIENT: received message - %s -\n",buffer);
	}while(strncmp(msgs,endstr,3)!=0);
	close(clientsocketfd);
	return 0;	
		
	
}
