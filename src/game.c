#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "./headers/matrice.h"
#include "./headers/traitement.h"
#include "./headers/interaction.h"
#include "./headers/const.h"

// Function to parse IP and port from a given input string
void parseIpPort(char* input, char* ip, int* port) {
    // Find the position of the colon in the input string
    char* colon = strchr(input, ':');
    if (colon == NULL) {
        // Error if colon is not found
        printf("Error: Invalid format. Use <ip>:<port>\n");
        exit(1);
    }

    // Copy the IP part from the start of the string up to the colon
    strncpy(ip, input, colon - input);
    ip[colon - input] = '\0';  // Null-terminate the IP string

    // Convert the port part (after the colon) from string to integer
    *port = atoi(colon + 1);
    if (*port == 0) {
        // Error if port conversion results in 0, indicating invalid port
        printf("Error: Invalid port.\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    // Default IP and port values
    char ip[16] = "127.0.0.1";  // Default local IP
    int port = 5555;            // Default port
    int ia_mode = 0;            // AI mode disabled by default

    int M[7][9], index[2] = {-1, -1};
    char input[2];
    remplissage(M);

    // Checking the number of arguments
    if (argc < 2) {
        printf("Usage: %s -s <port> [-ia] (for server) or %s -c <ip>:<port> [-ia] (for client) or %s -l (for local)\n", argv[0], argv[0], argv[0]);
        return 1;
    }

    // Checking if AI is activated via the -ia argument
    if (argc >= 4 && strcmp(argv[argc-1], "-ia") == 0) {
        ia_mode = 1;  // Enable AI mode
    }

    // Checking the selected mode (-s, -c or -l)
    if (strcmp(argv[1], "-s") == 0) {
        // Server mode
        if (argc < 3) {
            printf("Error: port is required for server mode.\n");
            return 1;
        }
        port = atoi(argv[2]);  // Extract the port
        if (port == 0) {
            printf("Error: invalid port.\n");
            return 1;
        }

        if (ia_mode) {
            printf("Starting in AI server mode on 127.0.0.1:%d\n", port);
            joueServeurAI(input, index, M, ip, port);  // Start as AI server
        } else {
            printf("Starting in server mode on 127.0.0.1:%d\n", port);
            joueServeur(input, index, M, ip, port);  // Start as normal server
        }

    } else if (strcmp(argv[1], "-c") == 0) {
        // Client mode
        if (argc < 3) {
            printf("Error: IP and port are required for client mode.\n");
            return 1;
        }
        parseIpPort(argv[2], ip, &port);  // Extract IP and port
        if (ia_mode) {
            printf("Starting in AI client mode. Connecting to %s:%d\n", ip, port);
            joueClientAI(input, index, M, ip, port);  // Start as AI client
        } else {
            printf("Starting in client mode. Connecting to %s:%d\n", ip, port);
            joueClient(input, index, M, ip, port);  // Start as normal client
        }

    } else if (strcmp(argv[1], "-l") == 0) {
        // Local player vs player mode
        joueLocal(input, index, M);

    } else {
        printf("Error: invalid option. Use -s for server, -c for client, or -l for local.\n");
        return 1;
    }

    return 0;
}



