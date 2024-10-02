/**
* "network.h"
*/
#ifndef NETWORK_H
#define NETWORK_H

#include <sys/socket.h>
#include <arpa/inet.h>

/**  Function to initialize a client socket
* Parameters:
*   @param ip: The IP address of the server to connect to
*   @param port: The port number on the server to connect to
* Returns:
*   @return The socket file descriptor on success, or -1 on failure
*/
int initClientSocket(const char* ip, int port);

/** Function to initialize a server socket
* @param Parameters:
* @param  port: The port number on which the server will listen for incoming connections
* Returns:
*   @return The socket file descriptor on success, or -1 on failure
*/
int initServerSocket(int port);

/** Function to accept a client connection on a server socket
* Parameters:
*   @param server_sock: The socket file descriptor of the server
* Returns:
*   @return The socket file descriptor for the accepted client connection, or -1 on failure
*/
int accepterClient(int server_sock);

#endif // NETWORK_H


