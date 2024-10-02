#ifndef INTERACTION_H
#define INTERACTION_H

/**
* Checks if the given move is a losing move like "a1" or "A1"
*/
int coupPerdant(const char *input);

/**
* Updates from an A1 type coordinate
*/
void miseAJourParReseau(char input[2], int index[2]);

/**
* Gets the move from the user and converts it to matrix indices
*/
void saisie(char input[2], int index[2]);

/**
* Manages the client side of the game: connects to server, sends and receives moves
*/
void joueClient(char input[2], int index[2], int mat[7][9], const char* ip, int port);

/**
* Manages the server side of the game: accepts client connections, receives and sends moves
*/
void joueServeur(char input[2], int index[2], int mat[7][9], const char* ip, int port);

/**
* Handles local gameplay between two players on the same machine
*/
void joueLocal(char input[2], int index[2], int mat[7][9]);

/**
* Starts a server that sends AI generated moves
*/
void joueServeurAI(char input[2], int index[2], int mat[7][9], const char* ip, int port);

/**
* Starts a client that sends AI generated moves
*/
void joueClientAI(char input[2], int index[2], int mat[7][9], const char* ip, int port);

#endif
