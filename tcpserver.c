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
	int socket_desc, connectionFd, c;
	struct sockaddr_in servaddr, client;
	time_t currentTime;
	
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		printf("Creating socket failed...\n");
		exit(0);
	}
	else
	{
		printf("Socket successfully created...\n");
		bzero(&servaddr, sizeof(servaddr));
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if((bind(socket_desc, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
	{
		printf("Bind failed...\n");
		exit(0);
	}
	else
	{
		printf("Bind success...\n");
	}
	
	if ((listen(socket_desc,5)) != 0)
	{
		printf("Listening failed...\n");
		exit(0);
	}
	else
	{
		printf("Listening...\n");
		c = sizeof(client);
	}


	
	connectionFd = accept(socket_desc, (struct sockaddr *)NULL, NULL);
	time(&currentTime);
	printf("Time requested at %s", ctime(&currentTime));
	send(connectionFd, ctime(&currentTime), 30, 0);
	
	return 0;
}

