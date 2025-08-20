#include<stdio.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    //step1: create the socket
    //socket -> has ip address, port address and the transimission protocol it uses
    int socket_file_discriptor = socket(AF_INET, SOCK_STREAM, 0);

    //step2: bind the socket to an IP and port 
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(8080);
    bind(socket_file_discriptor, (struct sockaddr*)&address, sizeof(address));

    //step3: Listen for incoming connections
    listen(socket_file_discriptor, 4); //maximum 3 pending connections

    printf("server is running and listening on port 8080...\n");

    while(1) {
        //Step 4: Accept an incomming connection (Three - way  handshake happens here) 
        int addrlen = sizeof(address);
        int new_socket = accept(socket_file_discriptor, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        printf("new socket: %d\n", new_socket);
        if (new_socket < 0) {
            perror("Failed to accept connection");
            continue;
        }

        printf("connection accepted\n");

        //Step 5: Handle data transfer
        char buffer[1024] = {0};
        read(new_socket, buffer, 1024); //Read data from client
        printf("Client message: %s\n", buffer);

        char *response = "Hello from the server!";
        write(new_socket, response, strlen(response));
        printf("response: %s\n", response);

        close(new_socket);
        printf("Connection closed....\n");
    }

    close(socket_file_discriptor);
    return 0;
    //
}