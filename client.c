#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main(int argc, char const *argv[])
{
    // create a socket
    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    // create a tcp socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+] TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to server
    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connected to server.\n");

    // Fill buffer with 0s
    bzero(buffer, 1024);
    strcpy(buffer, "HELLO, THIS IS CLIENT.\n");
    printf("Client: %s\n", buffer);

    // Send message to server
    send(sock, buffer, strlen(buffer), 0);

    // Receive message from server
    bzero(buffer, 1024);
    recv(sock, buffer, sizeof(buffer), 0);
    printf("Server: %s", buffer);

    close(sock);
    printf("Disconnected from the server.\n");

    return 0;
}