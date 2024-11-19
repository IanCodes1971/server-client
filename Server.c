#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[MAXLINE] = {0};
    char *greeting = "You are connected to the chat server!";
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    
    // Define the address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind the socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    
    printf("Waiting for a connection...\n");
    
    // Accept a connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                             (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    
    // Send a greeting message
    send(new_socket, greeting, strlen(greeting), 0);
    
    // Chat loop
    while (1) {
        memset(buffer, 0, MAXLINE);
        int valread = read(new_socket, buffer, MAXLINE);
        if (valread > 0) {
            printf("Client: %s\n", buffer);
            printf("You: ");
            fgets(buffer, MAXLINE, stdin);
            send(new_socket, buffer, strlen(buffer), 0);
        }
    }
    
    return 0;
}


