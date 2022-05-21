#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <time.h>

#define MAX_BUFFER 128
#define DAYTIME_SERVER_PORT 13

int main (void) 
{
	int serverFd, connectionFd, socket_desc, new_socket, c;
	struct sockaddr_in servaddr;
	char timebuffer[MAX_BUFFER+1];
	time_t currentTime;
	
	//Create socket
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_desc == -1)
	{
		printf("Could not create socket");
	}

	//Prepare the sockaddr_in structure
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(DAYTIME_SERVER_PORT);

	//Bind
	if(bind(socket_desc, (struct sockaddr *)&servaddr, sizeof(servaddr))<0)
	{
		puts("Bind failed");
		return 1;
	}

	puts("Bind done");
	
	//Listen
	listen(serverFd, 5);
	
	//Accept and incoming connectionns...
	puts("Waiting for incoming connections...");
	while(1) {
	
		connectionFd = accept(serverFd, (struct sockaddr *)NULL, NULL);
		
		if (connectionFd >= 0) {
			currentTime = time(NULL);
			snprintf(timebuffer, MAX_BUFFER, "%s\n", ctime(&currentTime));
		write(connectionFd, timebuffer, strlen(timebuffer));
		close(connectionFd);
		}
	}
}
		

