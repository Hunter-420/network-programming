#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define IP "192.168.1.157"
#define PORT 9999

int main(int argc, char *argv[])
{
    char writeBuffer[100] = "Hello I am Client";
    char readBuffer[100];

    int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockfd < 0) {
        perror("socket creation failed: ");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    int confd = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    if (confd == -1) {
        perror("connection establishment failed: ");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("client message: %s\n",writeBuffer);
    write(sockfd, writeBuffer, sizeof(writeBuffer));
    read(sockfd, readBuffer, sizeof(readBuffer));
    printf("server response: %s\n",readBuffer);

    close(confd);
    close(sockfd);
    return 0;
}
