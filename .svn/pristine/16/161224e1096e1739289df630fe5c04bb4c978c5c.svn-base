#include <stdio.h>
#include <ctype.h>
#include "traitement.h"
#include "matrice.h"
#include "interaction.h"
#include "const.h"

const int position_weights[7][9] = {
    {1, 3, 4, 4, 4, 4, 4, 3, 3}, // Row 0 weights
    {3, 4, 5, 5, 5, 5, 5, 4, 3}, // Row 1 weights
    {4, 5, 6, 6, 6, 6, 6, 5, 4}, // Row 2 weights
    {4, 5, 6, 7, 7, 7, 6, 5, 4}, // Row 3 weights
    {4, 5, 6, 6, 6, 6, 6, 5, 4}, // Row 4 weights
    {3, 4, 5, 5, 5, 5, 5, 4, 3}, // Row 5 weights
    {3, 3, 4, 4, 4, 4, 4, 3, 3}  // Row 6 weights
};

void vider_tampon(void);

/**
* The function traduction converts a character-based grid position (like "A1") into a numeric index
*/
void traduction(char input[2], int index[2]){
    /**
    * Array of characters representing the letters of the alphabet (A to I).
    */
    char alphabet[] = {'A','B','C','D','E','F','G','H','I'};
    
    /**
    * Integer variable to use in the loop.
    */
    int i;

    /**
    * Check if the second character (number) in the input is between 0 and 7 (inclusive).
    * If the number is valid, store it in index[0] after subtracting 1 (to match 0-based indexing).
    */
    if(input[1]-'0'<=7 && input[1]-'0'>=0){
        index[0] = input[1] - '0' - 1;
    }

    /**
    * Loop through the alphabet array to find a match for the first character (A to I).
    * Convert the input letter to uppercase and compare it with each letter in the alphabet array.
    * When a match is found, store the corresponding index in index[1].
    */
    for(i = 0; i < 9; i++) {
        if(toupper(input[0]) == alphabet[i]) {
            index[1] = i;
        }
    }
}

void traductionAI(char input[2], int index[2]){
    char alphabet[] = {'A','B','C','D','E','F','G','H','I'};
    input[0]=alphabet[index[1]];
    input[1]='0'+index[0]+1;
    printf("%c %c",input[0],input[1]);
}

/**
* The function saisie_valide checks whether the input string is a valid grid position (e.g., "A1")
*/
int saisie_valide(char input[3]){
    /**
    * Check if the first character is a valid letter between 'A' and 'I' (case insensitive).
    * Convert input[0] to uppercase and ensure it's within the range 'A' to 'I'.
    */
    return (toupper(input[0]) >= 'A' && toupper(input[0]) <= 'I') &&

           /**
           * Check if the second character is a valid number between '1' and '7'.
           * This ensures the numeric input is within the valid range.
           */
           (input[1] >= '1' && input[1] <= '7') &&

           /**
           * Check if the third character is the null terminator '\0',
           * confirming that the input string is exactly 2 characters long.
           */
           (input[2] == '\0');
}

void vider_tampon() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
* Checks if the selected cell in the matrix has already been eliminated
*/
int verifierSelectionDeLaCase(int myRow, int myColumn, int mat[7][9]) {
    if (mat[myRow][myColumn] == 0) {
        //printf("La case n'a pas encore été sélectionnée\n");
        return TRUE;
    } else {
        //printf("La case a déjà été sélectionnée, choisissez-en une autre\n");
        return FALSE;
    }
}

/**
* Counts the number of valid cells starting from the selected cell
*/
int compteurCasesValides(int myRow, int myColumn, int mat[7][9]) {
    int compteur = 0;
    int i, j;

    for (i = myRow; i < 7; i++) {
        if (mat[i][myColumn] == 0) {
            for (j = myColumn; j < 9; j++) {
                if (mat[i][j] == 0) {
                    compteur++;
                }
            }
        }
    }

    return compteur;
}

/**
* Updates the matrix by setting elements to 1 if the number of valid cells is less than or equal to 1
*/
void modifierMatriceAvecCasesValides(int myRow, int myColumn, int mat[7][9]) {
    int compteur = 0;
    int i, j;

    for (i = myRow; i < 7; i++) {
        if (mat[i][myColumn] == 0) {
            for (j = myColumn; j < 9; j++) {
                if (mat[i][j] == 0) {
                    compteur++;
                    /** Display the coordinates of the element */
                    printf("L'élément matrix[%d][%d] vaut 0\n", i, j);
                    /** Set the element to 1 */
                    mat[i][j] = 1;
                }
            }
        }
    }
}

/**
* Checks the validity of the selected cell and makes necessary updates
*/
int verifierValiditeCase(int myRow, int myColumn, int mat[7][9]) {
    if (verifierSelectionDeLaCase(myRow, myColumn, mat) == TRUE) {
        int compteurValide = compteurCasesValides(myRow, myColumn, mat);
        
        /**
        * If the number of valid cells is acceptable, update them
        */
        if (compteurValide <= 5) {
            modifierMatriceAvecCasesValides(myRow, myColumn, mat);
            return TRUE;
        } else {
            printf("Trop de cases sélectionnées\n");
            return FALSE;
        }
    }
    return FALSE;
}

/**
* Checks if the selected cell is valid for AI's move
*/
int verifierValiditeCaseAi(int myRow, int myColumn, int mat[7][9]){
    if (verifierSelectionDeLaCase(myRow, myColumn, mat) == TRUE) {
        int compteurValide = compteurCasesValides(myRow, myColumn, mat);

        /**
        * If the number of valid cells is acceptable, the cell is valid for AI's move
        */
        if (compteurValide <= 5) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return FALSE;
}

/**
* Generates possible moves for the AI based on the current state of the matrix
*/
void genererPossibleMoves(int mat[7][9], PossibleMoves *possibleMoves){
    int i,j;
    possibleMoves->taille=0;
    for(i = 0;i<7;i++)
        for (j = 0; j < 9; j++)
            if(verifierValiditeCaseAi(i, j, mat)){
                possibleMoves->moves[possibleMoves->taille][0]=i;
                possibleMoves->moves[possibleMoves->taille][1]=j;
                possibleMoves->taille++;
            }
}
