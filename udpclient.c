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
        int socket_desc, len, n;
        struct sockaddr_in servaddr, client;
        char timebuffer[MAX_BUFFER+1];

        socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_desc == -1)
        {
                puts("Creating socket failed...\n");
                exit(0);
        }
        else
        {
                puts("Creating socket success...\n");
        }

	memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = INADDR_ANY;

	sendto(socket_desc, timebuffer, 29, 0, (struct sockaddr *) &servaddr,sizeof(servaddr)); 
    	puts("Time request sent.\n");   
    	n = recvfrom(socket_desc, timebuffer, 29, 0, (struct sockaddr *) &servaddr, &len); 
    	printf("Time form server : %s\n", timebuffer); 
    	close(socket_desc); 
    	return 0; 
}
