#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUFFER 128
#define PORT 13

int main (void) 
{
	//initialize
	int socket_desc, connectionFd;
	struct sockaddr_in servaddr;
	struct tm * timeinfo;
	time_t currentTime;
	
	//create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		puts("Creating socket failed...\n");
		exit(0);
	}
	else
	{
		puts("Socket successfully created...\n");
		bzero(&servaddr, sizeof(servaddr));
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	//bind
	if((bind(socket_desc, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
	{
		puts("Bind failed...\n");
		exit(0);
	}
	else
	{
		puts("Bind success...\n");
	}
	
	//listen
	if ((listen(socket_desc,5)) != 0)
	{
		puts("Listening failed...\n");
		exit(0);
	}
	else
	{
		puts("Listening...\n");
	}


	//accept connection
	connectionFd = accept(socket_desc, (struct sockaddr *)NULL, NULL);
	time(&currentTime);
	timeinfo = localtime(&currentTime);
	printf("Time requested at %s", asctime(timeinfo));
	send(connectionFd, asctime(timeinfo), 30, 0);
	

	puts("Server closing...\n");
	close(connectionFd);
	
	return 0;
}

