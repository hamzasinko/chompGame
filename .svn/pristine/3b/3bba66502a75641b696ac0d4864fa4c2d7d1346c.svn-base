#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "../headers/traitement.h"
#include "../headers/matrice.h"
#include "../headers/interaction.h"
#include "../headers/const.h"


// Test function for verifierValiditeCase if the cell is not selected
int test_case_selectionnee_0() {
    int myRow = 6;  // Row index to test
    int myColumn = 8;  // Column index to test

    // Initialize a 7x9 matrix with all values set to 0
    int matrice[7][9] = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}  // No selected case
    };

    const int expected = 1;  // Expected value indicating the case is valid
    const int actual = verifierValiditeCase(myRow, myColumn, matrice);  // Call the function to test

    // Check if the actual result matches the expected result
    if (actual != expected) {
        // Print an error message if there is a mismatch
        fprintf(stderr, "test_case_selectionnee_0 : expecting %d while got %d\n", expected, actual);
        return 0;  // Test failed
    }
    return 1;  // Test passed
}

// Test function for verifierValiditeCase if the cell is selected
int test_case_selectionnee_1(){
    int myRow = 6;  // Row index to test
    int myColumn = 8;  // Column index to test

    // Initialize a 7x9 matrix with all values set to 0
    int matrice[7][9] = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 1}  
    };

    // Expected value indicating the case is not valid
    const int expected = 0;
    const int actual = verifierValiditeCase(myRow, myColumn, matrice);  // Call the function to test

    // Check if the actual result matches the expected result
    if (actual != expected) {
        // Print an error message if there is a mismatch
        fprintf(stderr, "test_case_selectionnee_1 : expecting %d while got %d\n", expected, actual);
        return 0;  // Test failed
    }
    return 1;  // Test passed
}

// Function to test 'CompteurCasesValides'
int test_compteur_cases_valides(){
    int myRow = 5;
    int myColumn = 6;
    int matrice[7][9] = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 1}  // Selected case at (6, 8)
    };

    const int expected = 5;  // Expected number of valid cases around (5,6)
    const int actual = compteurCasesValides(myRow, myColumn, matrice);  // Call the function to test

    // Check if the actual result matches the expected result
    if (actual != expected) {
        // Print an error message if there is a mismatch
        fprintf(stderr, "test_compteur_cases_valides : expecting %d while got %d\n", expected, actual);
        return 0;  // Test failed
    }
    return 1;  // Test passed
}

// Test function for modifierMatriceAvecCasesValides
int test_modifierMatriceAvecCasesValides() {
    // 1. Initialize the test matrix with all values set to 0 except for one selected case
    int matrice[7][9] = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 1}  // Selected case at (6, 8)
    };

    // 2. Call the function to modify the matrix starting from position (5, 6)
    int myRow = 5;
    int myColumn = 6;
    modifierMatriceAvecCasesValides(myRow, myColumn, matrice);

    // 3. Expected matrix after modification (cases around (5,6) should be updated)
    int expected[7][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 1, 1, 1},  // Modified cases around (5,6)
        {0, 0, 0, 0, 0, 0, 1, 1, 1}   // Modified cases around (5,6)
    };

    // 4. Compare the modified matrix with the expected matrix
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            // If any difference is found between the matrices
            if (matrice[i][j] != expected[i][j]) {
                return 0; // Test failed
            }
        }
    }
    return 1; // Test passed if all cases match
}

// Test VerifierValiditeCase if the cell is not selected and the count of valid cases is more than 5
int test_verifier_validite_case_more_than_5(){
    int myRow = 6;  // Row index to test
    int myColumn = 0;  // Column index to test

    int matrice[7][9] = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 1}  
    };
    
    const int expected = 0;  // Expected value indicating the case is not valid

    const int actual = verifierValiditeCase(myRow, myColumn, matrice);  // Call the function to test

    // Check if the actual result matches the expected result
    if (actual != expected) {
        // Print an error message if there is a mismatch
        fprintf(stderr, "test_verifier_validite_case_more_than_5 : expecting %d while got %d\n", expected, actual);
        return 0;  // Test failed
    }
    return 1;  // Test passed

} 

int test_verifierValiditeCaseAi(){
     // Plateau de jeu (0 représente une case libre, 1 représente une case déjà prise)
    int mat[7][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    // Tester la validité de la sélection d'une case
    int row = 6, col = 6;
    if (verifierValiditeCaseAi(row, col, mat) == TRUE)
        return 1;
    else 
        return 0;
}
int testGenererPossibleMoves() {
    int mat[7][9] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    PossibleMoves possibleMoves;
    int initialTaille = possibleMoves.taille;
    genererPossibleMoves(mat, &possibleMoves);

    if (possibleMoves.taille != initialTaille) {
        return 1; // taille has changed
    }
    return 0; // taille has not changed
}
// Test function for saisie_valide
int testSaisieValide() {
    // Array of strings (array of char pointers)
    char *validInputs[] = {"A1", "B7", "I3", "H5", "d2"};
    char *invalidInputs[] = {"J1", "A8", "G0", "B12", "Z7", "AA", "7A", ""};

    // Check valid inputs
    for (int i = 0; i < 5; i++) {
        if (!saisie_valide(validInputs[i])) {
            return 0; // Return 0 if any valid input is incorrectly marked as invalid
        }
    }

    // Check invalid inputs
    for (int i = 0; i < 8; i++) {
        if (saisie_valide(invalidInputs[i])) {
            return 0; // Return 0 if any invalid input is incorrectly marked as valid
        }
    }

    return 1; // Return 1 if all inputs behave correctly
}

// Fonction de test de la conversion
int verifie_conversion() {
    char inputs[4][2] = {"A1", "B3", "I7", "H2"};
    int expected_indices[4][2] = {{0, 0}, {2, 1}, {6, 8}, {1, 7}};
    int indices[4][2];
    int i;

    for(i = 0; i < 4; i++) {
        traduction(inputs[i], indices[i]);
        // Vérifier si les indices obtenus correspondent aux indices attendus
        if(indices[i][0] != expected_indices[i][0] || indices[i][1] != expected_indices[i][1]) {
            return 0; // Conversion invalide
        }
    }
    return 1; // Conversion valide
}

// Test function for traductionAI
int test_traductionAI() {
    char input[2];
    int index[2];

    // Test case 1
    index[0] = 0;  // Row 0
    index[1] = 0;  // Column A (0 in the alphabet array)
    traductionAI(input, index);
    if (input[0] != 'A' || input[1] != '1') {
        return 0;  // Test failed
    }

    // Test case 2
    index[0] = 6;  // Row 6
    index[1] = 8;  // Column I (8 in the alphabet array)
    traductionAI(input, index);
    if (input[0] != 'I' || input[1] != '7') {
        return 0;  // Test failed
    }

    // Test case 3
    index[0] = 3;  // Row 3
    index[1] = 4;  // Column E (4 in the alphabet array)
    traductionAI(input, index);
    if (input[0] != 'E' || input[1] != '4') {
        return 0;  // Test failed
    }

    // All tests passed
    return 1;
}