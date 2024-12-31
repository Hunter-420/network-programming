#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>


#define IP "192.168.1.157"
#define PORT 9999


int main(int argc, char *argv[])
{
    char message[100] = "Hello I am echo";
    char recvBuffer[100];

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0 ) {
        perror("socket creation failed: \n");
        exit(1);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&server, sizeof(server));
    printf("message from client: %s\n",message);

    socklen_t serverlen = sizeof(server);
   int i =  recvfrom(sockfd, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr *)&server, &serverlen);
    printf("message from server: %s\n",recvBuffer);
    close(sockfd);
    return 0;
}
