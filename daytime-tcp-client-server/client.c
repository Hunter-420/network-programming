/*
 tcp client flow
 socket
 connect
 write 
 read   
 close
*/

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
    char readBuffer[100];
    char writeBuffer[] = "what's the current time";
    
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(IP);
    server.sin_port = htons(PORT);

    int confd = connect(socket_fd, (struct sockaddr *)&server, sizeof(server));
    if (confd == -1) {
        perror("connection failed: \n");
        exit(EXIT_FAILURE);
    }

    printf("connection established with server IP: %s && PORT: %d ...\n",IP,PORT);
    printf("client requesting to server: %s\n",writeBuffer);
    write(socket_fd, writeBuffer, sizeof(writeBuffer));
   // printf("requesting to server: %s\n",writeBuffer);

   int i = read(socket_fd, readBuffer, sizeof(readBuffer));
    printf("%d byte recived from server && respons from server: %s\n",i,readBuffer);

    close(confd);
    close(socket_fd);
    

    return 0;
}
