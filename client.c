// client side

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#ifndef PORT
#define PORT 8080
#endif

int main(int argc, const char * argv[]){
    int sock = 0, valread;
    struct sockaddr_in server_address;
    char buffer[1024] = {0}, message[1024] = {0};
    
    // initializing socket address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    
    // initializing socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){  // test
        perror("[-] socket creation failed\n");
        exit(EXIT_FAILURE);
    }else printf("[+] socket created\n");
    
    if(inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0){
        perror("[-] invalid address\n");
        exit(EXIT_FAILURE);
    }
    
    // making connection with server
    if(connect(sock, (struct sockaddr*) &server_address, sizeof(server_address)) < 0){
        perror("[-] failed to connect\n");
        exit(EXIT_FAILURE);
    }else printf("[+] connection established with server\n");
    
    
    // sending packages
    printf("send: ");
    scanf("%[^\n]", message);
    send(sock, message, strlen(message), 0);
    
    valread = read(sock, buffer, 1024);
    printf("server: %s\n", buffer);
    
    return EXIT_SUCCESS;
}
