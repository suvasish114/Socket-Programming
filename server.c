// server side

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef PORT
#define PORT 8080
#endif

int main(int argc, const char * argv[]) {
    struct sockaddr_in address;
    int opt = 1, new_socket, val_read, address_len = sizeof(address);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    char buffer[1024] = {0}, message[1024] = {0};
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    address.sin_family = AF_INET;
    
    // initializing socket
    if( server_fd == 0){
        perror("[-] socket failed\n");
        exit(EXIT_FAILURE);
    }else{
        printf("[+] socket creation successful\n");
    }
    
    // binding socket with the port
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))){
        perror("[-] faild to set socket opt\n");
        exit(EXIT_FAILURE);
    }else printf("[+] socket opt set\n");
    
    if(bind(server_fd, (struct sockaddr*) &address, sizeof(address)) < 0){
        perror("[-] socket binding failed\n");
        exit(EXIT_FAILURE);
    }else printf("[+] socket binded to port %d\n", PORT);
    
    // listning mode
    if(listen(server_fd, 3) < 0){
        perror("[-] listning failed\n");
        exit(EXIT_FAILURE);
    }else printf("[+] listning...\n");
    
    // making connection with client
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&address_len);
    if(new_socket < 0){
        perror("[-] accepting failure\n");
        exit(EXIT_FAILURE);
    }else printf("[+] connection established with client\n");
    
    // sending packages
    val_read = read(new_socket, buffer, 1024);
    printf("client: %s\n", buffer);
    
    printf("send: ");
    scanf("%[^\n]", message);
    send(new_socket, message, strlen(message), 0);
    
    return EXIT_SUCCESS;
}
