#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    // create a socket
    char *ip = "127.0.0.1";
    int port = 5567;
    pid_t pid;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    // create a tcp socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+] TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0) {
        close(server_sock); 
        perror("[-] Bind error");
        exit(1);
    }
    printf("[+]Binded to port number: %d\n", port);

    // Listen for client
    listen(server_sock, 5);
    printf("Listening...\n");
    // accept connection from client
    addr_size = sizeof(client_addr);
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    printf("[+] Client connected.\n");

    for (;;) {
        
        // receive message from client  
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf("Client: %s", buffer);

        time_t t;
        time(&t);

        bzero(buffer, 1024);
        strcpy(buffer, ctime(&t));
        printf("Server: %s", buffer);
        send(client_sock, buffer, sizeof(buffer), 0);
       
    }
    close(client_sock); 
    printf("[+]Client disconnected.\n\n");
    
    return 0;
}
