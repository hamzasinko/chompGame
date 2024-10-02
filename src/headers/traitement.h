/**
* "traitement.h"
*/

#ifndef TRAITEMENT_H
#define TRAITEMENT_H

/**
* Define a structure to hold possible moves
*/
typedef struct {
    int moves[64][2]; // Array to store up to 64 possible moves, each move consisting of 2 integers (e.g., row and column)
    int taille;      // Number of valid moves stored in the 'moves' array
} PossibleMoves;

// Function prototypes

/**
* Converts a string input to an index array
*/
void traduction(char input[2], int index[2]);

void traductionAI(char input[2], int index[2]);

/**
* Validates the user input for move commands
*/
int saisie_valide(char input[3]);

// Clears the input buffer (used to handle extra characters in input)
void vider_tampon();

/**
* Checks if the selected cell in the matrix is valid
*/
int verifierSelectionDeLaCase(int myRow, int myColumn, int mat[7][9]);

/**
* Counts the number of valid cells surrounding a given cell in the matrix
*/
int compteurCasesValides(int myRow, int myColumn, int mat[7][9]);

/**
* Updates the matrix based on the number of valid cells around a given cell
*/
void modifierMatriceAvecCasesValides(int myRow, int myColumn, int mat[7][9]);

/**
* Checks if the selected cell is valid in the matrix
*/
int verifierValiditeCase(int myRow, int myColumn, int mat[7][9]);

/**
* Checks if the selected cell is valid for AI's move
*/
int verifierValiditeCaseAi(int myRow, int myColumn, int mat[7][9]);

/**
* Generates possible moves for the AI based on the current state of the matrix
*/
void genererPossibleMoves(int mat[7][9], PossibleMoves *possibleMoves);

#endif // TRAITEMENT_H
