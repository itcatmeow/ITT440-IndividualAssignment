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
        int socket_desc, connectionFd, len, n;
        struct sockaddr_in servaddr, client;
	char timebuffer[MAX_BUFFER+1];
        time_t currentTime;

        socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
        if (socket_desc == -1)
        {
                printf("Creating socket failed...\n");
                exit(0);
        }
        else
        {
                printf("Socket successfully created...\n");
        }

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&client, 0, sizeof(client));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = INADDR_ANY;
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
	
	len = sizeof(client);
	
	n = recvfrom(socket_desc, timebuffer, MAX_BUFFER, MSG_WAITALL, (struct sockaddr *)&client, &len);
        time(&currentTime);
        printf("Time requested at %s", ctime(&currentTime));
        sendto(connectionFd, ctime(&currentTime), 30, 0, 0, 0);

        return 0;
}
