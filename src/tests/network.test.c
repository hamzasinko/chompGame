#include <stdio.h>
#include <arpa/inet.h> 
#include <sys/socket.h> 
#include <unistd.h>  
#include "../headers/traitement.h"
#include "../headers/matrice.h"
#include "../headers/interaction.h"
#include "../headers/const.h"
#include "../headers/network.h"
#include "../headers/ai.h"
#include "../headers/aiV1.h"

int test_initClientSocket() {
    // Cas de test 1 : Connexion réussie 
    const char* ip = "127.0.0.1";  // Adresse de loopback (localhost)
    int port = 5555;  // Port à tester 
    
    int sock = initClientSocket(ip, port);  // Appel de la fonction à tester

    if (sock >= 0) {  // Si un descripteur de socket valide est renvoyé, le test réussit
        printf("Test réussi : Connexion réussie à %s:%d\n", ip, port);
        close(sock);  // Ferme la socket après le test
        return 1;
    } else {
        printf("Test échoué : Impossible de se connecter à %s:%d\n", ip, port);
        return 0;
    }
}

int initServerSocket(int port);  // Prototype pour créer un socket serveur

// Fonction de test pour accepter un client
int test_accepterClient() {
    // Initialiser un socket serveur pour écouter sur le port 5555
    int server_sock = initServerSocket(5555);
    if (server_sock < 0) {
        printf("Failed to initialize server socket\n");
        return 0;  // Échec du test si le socket serveur n'a pas pu être créé
    }

    printf("Waiting for a client to connect...\n");

    // Appel de la fonction à tester : accepter une connexion client
    int client_sock = accepterClient(server_sock);

    // Vérifier si un client a été accepté
    if (client_sock >= 0) {
        printf("Test passed: Client connected successfully.\n");
        close(client_sock);  // Fermer le socket client après le test
        close(server_sock);  // Fermer le socket serveur après le test
        return 1;  // Succès du test
    } else {
        printf("Test failed: Could not accept client connection.\n");
        close(server_sock);  // Fermer le socket serveur en cas d'échec
        return 0;  // Échec du test
    }
}
// Prototype de la fonction que nous testons
int initServerSocket(int port);

int test_initServerSocket() {
    int port = 5555;  // Choisissez un port pour le test
    int server_sock = initServerSocket(port);  // Appel de la fonction à tester

    if (server_sock >= 0) {  // Vérifie si le socket du serveur a été créé avec succès
        printf("Test réussi : Le serveur a bien été initialisé sur le port %d\n", port);
        close(server_sock);  // Ferme la socket après le test
        return 1;  // Le test est réussi
    } else {
        printf("Test échoué : Impossible d'initialiser le serveur sur le port %d\n", port);
        return 0;  // Le test a échoué
    }
}
