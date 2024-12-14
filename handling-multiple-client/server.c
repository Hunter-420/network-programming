#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>

#define IP "192.168.1.157"
#define PORT 9999

/*
    TCP server flow
    socket
    bind
    listen
    accept
    read ---> connection fd 
    write ---> connection fd
    close
*/

int main(int argc, char *argv[])
{
    char writeBuffer[100] = "I am TCP Server";
    char readBuffer[100];
    char clientIPBuffer[100];

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket creation failed: ");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
   
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    int bindfd = bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (bindfd == -1) {
        perror("bind failed: ");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("server listening on IP: %s && PORT: %d\n",IP,PORT);

    int backlog = 5;
    listen(sockfd, backlog);

    while (1) {

        socklen_t addr_len = sizeof(client);
        int confd = accept(sockfd, (struct sockaddr *)&client, &addr_len);
        if (confd < 0) {
            perror("connection accept failed: ");
            close(sockfd);
            exit(EXIT_FAILURE);
        }
        
        inet_ntop(AF_INET, &client.sin_addr, clientIPBuffer, sizeof(clientIPBuffer));
        printf("client connected from IP: %s && PORT %d ...\n",clientIPBuffer,ntohs(client.sin_port));

        pid_t pid = fork();

        if (pid == 0) {
            //client section
            close(sockfd);
            read(confd, readBuffer, sizeof(readBuffer));
            printf("client message: %s\n",readBuffer);
            write(confd, writeBuffer, sizeof(writeBuffer));
            printf("server respond: %s\n",writeBuffer);
            close(confd);
            exit(EXIT_SUCCESS);
        }
        close(confd);
    }

    close(sockfd);
    return 0;
}
