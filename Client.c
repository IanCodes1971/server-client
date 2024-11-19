#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[MAXLINE] = {0};
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IP address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/Address not supported\n");
        return -1;
    }
    
    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed\n");
        return -1;
    }
    
    // Receive greeting message
    read(sock, buffer, MAXLINE);
    printf("Server: %s\n", buffer);
    
    // Chat loop
    while (1) {
        printf("You: ");
        fgets(buffer, MAXLINE, stdin);
        send(sock, buffer, strlen(buffer), 0);
        
        memset(buffer, 0, MAXLINE);
        int valread = read(sock, buffer, MAXLINE);
        if (valread > 0) {
            printf("Server: %s\n", buffer);
        }
    }
    
    return 0;
}



