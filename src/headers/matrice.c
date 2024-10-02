#include <stdio.h>
#include "matrice.h"

/**
* Initializes a 7x9 matrix with zeros.
*/
void remplissage(int mat[7][9]){
    int i, j;
    for(i=0; i<7; i++)
        for(j=0; j<9; j++)
            mat[i][j] = 0;
}

/**
* Displays a 7x9 matrix with color-coded blocks.
*/
void affichage(int mat[7][9]){
    int i, j;
    /**
    * Print column headers
    */
    printf("\n   \e[0;37mA   B   C   D   E   F   G   H   I\e[0m\n");
    for(i=0; i<7; i++){
        /**
        * Print row numbers
        */
        printf("\e[0;37m%d \e[0m", i+1);
        for(j=0; j<9; j++){
            /**
            * Print color-coded blocks based on matrix values
            */
            if (mat[i][j] == 0){
                printf("\e[0;101m\e[41m▓▓▓\e[0m ");
            }
            else{
                printf("\e[0;31m\e[41m▓▓▓\e[0m ");
            }
        }
        printf("\n\n"); // New line after each row
    }
}
