#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_BUFFER 128
#define PORT 13

int main ()
{
	//initialize
        int socket_desc;
        struct sockaddr_in servaddr;
        char timebuffer[MAX_BUFFER+1];

	//create socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc == -1)
	{
		puts("Creating socket failed...\n");
		exit(0);
	}
	else
	{
		puts("Creating socket success...\n");
		bzero(&servaddr, sizeof(servaddr));
	}

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("192.168.56.103");

	//connect to server
        if(connect(socket_desc, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
	{
		puts("Connection failed...\n");
		exit(0);
	}
	else
	{
		puts("Connected to the server...\n");
	}
	
	//display output
        recv(socket_desc, timebuffer, 29, 0);
	printf("Time from server: %s\n", timebuffer);

	close(socket_desc);

	return(0);
}

