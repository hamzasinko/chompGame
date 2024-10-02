#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

/**
* Function to initialize a client socket and connect to a server
*/
int initClientSocket(const char* ip, int port) {
    int sock;
    struct sockaddr_in addr;

    /**
    * Create a socket
    */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Error creating socket");
        return -1;
    }

    /**
    * Prepare the sockaddr_in structure
    */
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    /**
    * Attempt to connect to the server
    */
    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Error connecting to server");
        close(sock);
        return -1;
    }

    printf("Successfully connected to server %s on port %d\n", ip, port);
    return sock;  // Return the connected socket
}

/**
* Function to initialize a server socket and listen on a given port
*/
int initServerSocket(int port) {
    int server_sock;
    struct sockaddr_in server_addr;

    /**
    * Create a socket
    */
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("Error creating socket");
        return -1;
    }

    /**
    * Prepare the sockaddr_in structure
    */
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;  // Listen on all interfaces

    /**
    * Bind the socket to the specified port
    */
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        close(server_sock);
        return -1;
    }

    /**
    * Start listening for incoming connections
    */
    if (listen(server_sock, 5) < 0) {
        perror("Error listening on socket");
        close(server_sock);
        return -1;
    }

    printf("Server listening on port %d\n", port);
    return server_sock;  // Return the server socket
}

/**
* Function to accept a client connection on the server
*/
int accepterClient(int server_sock) {
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    int client_sock;

    /**
    * Accept an incoming connection
    */
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
    if (client_sock < 0) {
        perror("Error accepting client connection");
        return -1;
    }

    printf("Client connected from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return client_sock;  // Return the client socket
}
