#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>

int main()
{
	int serversocketfd=socket(AF_INET, SOCK_STREAM, 0);
	if(serversocketfd==0)
	{
		printf("\n ERROR: socket creation failed");
		return -1;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family=AF_INET;
	server_addr.sin_addr.s_addr=INADDR_ANY;
	server_addr.sin_port=htons(8082);

	int bind_return=bind(serversocketfd, (struct sockaddr*)&server_addr,sizeof(server_addr));
	if(bind_return<0)
	{
		printf("\n ERROR: socket binding failed");
		close(serversocketfd);
		return -1;
	}
	printf("\n bind return: %d",bind_return);	

	int listen_return=listen(serversocketfd,3);
	if(listen_return<0)
	{
		printf("\n ERROR: socket listen failed");
		close(serversocketfd);
		return -1;
	}
	
	int sizeofaddr=sizeof(server_addr);
	int newsocket= accept(serversocketfd,(struct sockaddr*)&server_addr,(socklen_t*)&sizeofaddr);
	if(newsocket<0)
	{
		printf("\n ERROR: socket accept failed");
		close(newsocket);
		return -1;
	}

	char buffer[1024]={};
	read(newsocket, buffer, 1024);
	printf("\nSERVER: received - %s - from client",buffer); 
	send(newsocket,"hello",strlen("hello"),0);
	printf("\nSERVER: sent message");
	
	close(serversocketfd);
	return 0;
}

