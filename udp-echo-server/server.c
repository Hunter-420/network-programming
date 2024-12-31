#include <arpa/inet.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define IP "192.168.1.157"
#define PORT 9999


int main(int argc, char *argv[])
{
    char recvBuffer[100];
    char message[100] = "Hello I am Server";

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("socket creation failed: ");
        exit(1);
    }


    struct sockaddr_in server,client;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(IP);

    int socklen = sizeof(server);
    int bindfd = bind(sockfd, (struct sockaddr *)&server, socklen);
    if (bindfd == -1) {
        perror("bind failed: ");
        exit(1);
    }

    printf("server is listining on IP %s && PORT %d ...\n",IP,PORT);
    
    while(1){
    socklen_t clientlen = sizeof(client);
    recvfrom(sockfd, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr *)&client, &clientlen);
    printf("message from client: %s\n",recvBuffer);

    //   sendto(sockfd, message, sizeof(message), 0, (struct sockaddr *)&client, sizeof(client));
    
    sendto(sockfd, recvBuffer, sizeof(recvBuffer), 0, (struct sockaddr *)&client, sizeof(client));
    printf("message from server: %s\n",recvBuffer);
    }
    close(sockfd);
    return 0;
}
