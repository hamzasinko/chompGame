#include <stdio.h>
#include <ctype.h>
#include "interaction.h"
#include "traitement.h"
#include "matrice.h"
#include "const.h"
#include "aiV1.h"
#include "ai.h"
#include "network.h"
#include <sys/socket.h>
#include <arpa/inet.h>  // For inet_addr()
#include <string.h>     // For memset(), strcpy(), etc.
#include <stdlib.h>     // For exit()
#include <unistd.h>

/**
 * Checks if the given move is a losing move like "a1" or "A1".
 * @param input The move to check.
 * @return 1 if the move is a losing move, 0 otherwise.
 */
int coupPerdant(const char *input) {

    // Check if the input is "a1" or "A1"
    if (tolower(input[0]) == 'a' && input[1] == '1') {
        return 1; // Valid input
    }

    return 0; // Invalid input
}

// Function to get and validate user input
void saisie(char input[2], int index[2]){
    int isActive = 0;
    while (index[0] == -1 || index[1] == -1){
        do {
            // Prompt the user for input and validate it
            if (isActive == 0) {
                printf("Saisir une case sous la forme A1: ");
                isActive++;
            } else {
                printf("Case invalide, saisir une case sous la forme A1: ");
                vider_tampon(); // Clear the input buffer
            }
            scanf("%2s", input); // Read 2 characters of input
        } while (!saisie_valide(input)); // Validate the input
        traduction(input, index); // Translate input to matrix indices
    }
}

/**
 * Updates matrix based on received network data.
 * @param input The move received from the network.
 * @param index Array to store the matrix indices corresponding to the input.
 */
void miseAJourParReseau(char input[2], int index[2]){
    int isActive = 0;
    while (index[0] == -1 || index[1] == -1){
        traduction(input, index); // Translate received input to matrix indices
    }
}

/**
 * Manages client-side gameplay: connects to the server, sends and receives moves.
 * @param input Array to store the move made by the client.
 * @param index Array to store the matrix indices of the client's move.
 * @param mat The game matrix.
 * @param ip The server IP address.
 * @param port The server port.
 */
void joueClient(char input[2], int index[2], int mat[7][9], const char* ip, int port) {
    char buffer[1024];
    int result;
    
    // Initialize the client socket
    int sock = initClientSocket(ip, port);
    if (sock == -1) {
        printf("Échec de la connexion au serveur\n");
        return;
    }

    printf("Connecté\n");
    bzero(buffer, 1024); // Clear buffer
    affichage(mat); // Display the initial matrix

    // Main game loop
    while (mat[0][0] != 1) {
        // Get and validate the player's move
        do {
            index[0] = -1;
            index[1] = -1;
            saisie(input, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));
        
        // Send the move to the server
        if (input[0] != '\0') {
            strcpy(buffer, input);
            result = send(sock, buffer, strlen(buffer), 0);
            if (result < 0) {
                perror("Erreur lors de l'envoi du message");
                break; // Exit loop if sending fails
            } else {
                printf("Message envoyé avec succès (%d octets)\n", result);
            }
        }

        affichage(mat);
        printf("J'ai joué %s \n", input);
        
        // Check if the move is a losing move
        if (coupPerdant(input)) {
            printf("Vous avez perdu ! \n");
            break;
        }

        // Receive the server's move
        bzero(buffer, 1024);
        recv(sock, buffer, sizeof(buffer), 0);

        // Update the matrix based on the server's move
        do {
            index[0] = -1;
            index[1] = -1;
            miseAJourParReseau(buffer, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));
        
        affichage(mat);
        
        // Check if the server's move is a losing move
        if (coupPerdant(buffer)) {
            printf("Vous avez gagné !\n");
            break;
        }

        printf("Adversaire a joué :: %s\n", buffer);
    }

    // Close the socket after the game ends
    close(sock);
    printf("Partie finie, déconnexion.\n");
}

/**
 * Manages server-side gameplay: accepts client connections, and sends and receives moves.
 * @param input Array to store the move made by the server.
 * @param index Array to store the matrix indices of the server's move.
 * @param mat The game matrix.
 * @param ip The server IP address.
 * @param port The server port.
 */
void joueServeur(char input[2], int index[2], int mat[7][9], const char* ip, int port) {
    int result;
    char buffer[1024];
    
    // Initialize the server socket
    int server_sock = initServerSocket(port);
    if (server_sock == -1) {
        printf("Échec de l'initialisation du serveur\n");
        return;
    }

    // Accept a client connection
    int client_sock = accepterClient(server_sock);
    if (client_sock == -1) {
        printf("Échec de la connexion avec le client\n");
        close(server_sock);
        return;
    }

    affichage(mat); // Display the initial matrix

    // Main game loop
    while (mat[0][0] != 1) {
        // Wait for the client's move
        printf("En attente d'un message du client\n");
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        
        // Update the matrix based on the client's move
        do {
            index[0] = -1;
            index[1] = -1;
            miseAJourParReseau(buffer, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));
        
        affichage(mat);
        printf("Adversaire a joué : %s\n", buffer);

        // Check if the client's move is a losing move
        if (coupPerdant(buffer)) {
            printf("Vous avez gagné !\n");
            break;
        }

        // Get and validate the server's move
        do {
            index[0] = -1;
            index[1] = -1;
            saisie(input, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));

        affichage(mat);
        printf("J'ai joué %s \n", input);
        
        // Send the move to the client
        if (input[0] != '\0') {
            strcpy(buffer, input);
            result = send(client_sock, buffer, strlen(buffer), 0);
            if (result < 0) {
                perror("Erreur lors de l'envoi du message");
                break; // Exit loop if sending fails
            } else {
                printf("Message envoyé avec succès (%d octets)\n", result);
            }
        }
        
        // Check if the server's move is a losing move
        if (coupPerdant(input)) {
            printf("Vous avez perdu !\n");
            break;
        }
    }

    // Close the connection after the game ends
    close(client_sock);
    printf("Partie finie, déconnexion.\n");
}

/**
 * Manages local two-player gameplay on the same machine.
 * @param input Array to store the move made by the current player.
 * @param index Array to store the matrix indices of the player's move.
 * @param mat The game matrix.
 */
void joueLocal(char input[2], int index[2], int mat[7][9]) {
    affichage(mat); // Display the initial matrix
    while (mat[0][0] != 1) {
        printf("Au tour de Joueur 1:\n");
        // Get and validate player 1's move
        do {
            index[0] = -1;
            index[1] = -1;
            saisie(input, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));
        affichage(mat);
        printf("Joueur 1 a joué %s \n", input);
        
        // Check if player 1's move is a losing move
        if (coupPerdant(input)) {
            printf("Joueur 2 gagne! !\n");
            break;
        }

        printf("Au tour de Joueur 2:\n");
        // Get and validate player 2's move
        do {
            index[0] = -1;
            index[1] = -1;
            saisie(input, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));
        affichage(mat);
        printf("Joueur 2 a joué %s \n", input);

        // Check if player 2's move is a losing move
        if (coupPerdant(input)) {
            printf("Joueur 1 gagne! !\n");
            break;
        }
    }

    printf("Partie finie, déconnexion.\n");
}

void joueServeurAI(char input[2], int index[2], int mat[7][9], const char* ip, int port) {
int result;
Scores score;
score.score_p1=0;
score.score_p2=0;
    char buffer[1024];
    int server_sock = initServerSocket(port);  //Server initialization
    char move[3];
    if (server_sock == -1) {
        printf("Échec de l'initialisation du serveur\n");
        return;
    }

    int client_sock = accepterClient(server_sock);  // Waiting for a client connection

    if (client_sock == -1) {
        printf("Échec de la connexion avec le client\n");
        close(server_sock);
        return;
    }

    affichage(mat);
    while (mat[0][0] != 1) {

        // Since the client plays first, we wait for their message
        printf("En attente d'un message du client\n");
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);

        do {

            index[0] = -1;
            index[1] = -1;
            miseAJourParReseau(buffer, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));

        affichage(mat);
        printf("Adversaire a joué : %s\n", buffer);

        if (coupPerdant(buffer)) {
        printf("ServeurAI a gagné !\n");
        break;
        }

            aiMoveV1Min(mat, move, &score);
            do {
            index[0] = -1;
            index[1] = -1;
            miseAJourParReseau(move, index);
                    } while (!verifierValiditeCase(index[0], index[1], mat));

        affichage(mat);
        printf("ServeurAI a joué %s \n", move);

        // We send once the move is correctly inputted
            strcpy(buffer, move);
                result = send(client_sock, buffer, strlen(buffer), 0);
            if (result < 0) {
                perror("Erreur lors de l'envoi du message");
                break;  // Exit the loop if sending fails
            } else {
                printf("Message envoyé avec succès (%d octets)\n", result);
            }

        if (coupPerdant(move)) {
        printf("ServeurAI a perdu !\n");
        break;
        }

    }

    // Close the connection once the game is over
    close(client_sock);
    printf("Partie finie, déconnexion.\n");
}

void joueClientAI(char input[2], int index[2], int mat[7][9], const char* ip, int port) {

char* a1 = "a1";
char* A1 = "A1";
Scores score;
score.score_p1=0;
score.score_p2=0;

char buffer[1024];
    char move[3];
    int result;

    int sock = initClientSocket(ip, port);  //Client initialization

    if (sock == -1) {
        printf("Échec de la connexion au serveur\n");
        return;
    }

  printf("Connecté\n");

  bzero(buffer, 1024);
    affichage(mat);
    // We want to keep the connection for the duration of the game
    while (mat[0][0] != 1) {

        bzero(move, 3);
        aiMoveV1Max(mat, move, &score);

            do {
            index[0] = -1;
            index[1] = -1;
            miseAJourParReseau(move, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));

        // Here we send the move played, then wait for the server's move
        // If the input contains something, we send it
                    strcpy(buffer, move);
                        result = send(sock, buffer, strlen(buffer), 0);
            if (result < 0) {
                perror("Erreur lors de l'envoi du message");
                break;  // Exit the loop if sending fails
            } else {
                printf("Message envoyé avec succès (%d octets)\n", result);
            }

        affichage(mat);
        printf("ClientAI a joué %s \n", move);

        if (coupPerdant(move)) {
        printf("CLientAI a perdu ! \n");
        break;
        }

        // Here, it's the server's response
        bzero(buffer, 1024);
        recv(sock, buffer, sizeof(buffer), 0);

        // To be modified by the function that updates the matrix
        do {
            index[0] = -1;
            index[1] = -1;
            miseAJourParReseau(buffer, index);
        } while (!verifierValiditeCase(index[0], index[1], mat));

        affichage(mat);

        if (coupPerdant(buffer)) {
        printf("CLientAI a gagné !\n");
        break;
        }
}}
