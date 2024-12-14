#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define PORT 9999
#define IP "192.168.1.157" 

int main(int argc, char *argv[])
{

    char clientIPBuffer[100];
    char writeBuffer[100],readBuffer[100]; 
    time_t current_time;

    int server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (server_fd<0) {
        perror("socker creation failed: ");
        exit(EXIT_FAILURE);
    }
    
    struct sockaddr_in server_addr, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);

    

    int server_addr_len = sizeof(server_addr); 
    int socket_bind = bind(server_fd, (struct sockaddr *)&server_addr, (socklen_t)server_addr_len);

    if (socket_bind == -1) {
        perror("socket bind failed: ");
        exit(EXIT_FAILURE);
    }
   

    printf("server listening on IP: %s && PORT: %d ...\n",IP,PORT);

    int backlog = 2;
    listen(server_fd, backlog);

    int client_addr_len = sizeof(client_addr);
    int accept_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    
    if (accept_fd == -1) {
       perror("client request not accepted: ");
       exit(EXIT_FAILURE);
    }
    
    inet_ntop(AF_INET, &client_addr.sin_addr, clientIPBuffer, sizeof(clientIPBuffer));
    
    printf("client connected from IP: %s && PORT: %d ...\n",clientIPBuffer,ntohs(client_addr.sin_port));

  int i =  read(accept_fd, readBuffer, sizeof(readBuffer));
   printf("%d byte received && message from client: %s\n",i,readBuffer);

    //sending time to client 

    current_time = time(NULL);
    snprintf(writeBuffer, sizeof(writeBuffer), "%.24s\r\n",ctime(&current_time));
    printf("sending time %s: \n",writeBuffer);
    write(accept_fd, writeBuffer, sizeof(writeBuffer));

    close(accept_fd);
    close(server_fd);
    return EXIT_SUCCESS;
}
