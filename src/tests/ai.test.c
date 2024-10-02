#include "../headers/ai.h"
#include "../headers/const.h"
#include "../headers/traitement.h"
#include "../headers/matrice.h"
#include "ai.test.h"
#include <stdio.h>
#include <limits.h>
#include <string.h>

int test_sort_moves() {
    int board[7][9] = {0};  // Simulated board
    int dynamic_weights[7][9] = {
        {10, 30, 20, 50, 40, 60, 90, 70, 80},
        {10, 30, 20, 50, 40, 60, 90, 70, 80},
        {10, 30, 20, 50, 40, 60, 90, 70, 80},
        {10, 30, 20, 50, 40, 60, 90, 70, 80},
        {10, 30, 20, 50, 40, 60, 90, 70, 80},
        {10, 30, 20, 50, 40, 60, 90, 70, 80},
        {10, 30, 20, 50, 40, 60, 90, 70, 80}
    };
    Scores scores;
    scores.score_p1=0;
    scores.score_p2=0;

    PossibleMoves possibleMoves;
    possibleMoves.taille = 4;
    possibleMoves.moves[0][0] = 0; possibleMoves.moves[0][1] = 1;  // Move 1: (0, 1)
    possibleMoves.moves[1][0] = 0; possibleMoves.moves[1][1] = 3;  // Move 2: (0, 3)
    possibleMoves.moves[2][0] = 0; possibleMoves.moves[2][1] = 0;  // Move 3: (0, 0)
    possibleMoves.moves[3][0] = 0; possibleMoves.moves[3][1] = 4;  // Move 4: (0, 4)

    // Test case 1: Maximize
    sort_moves(board, &possibleMoves, dynamic_weights, &scores, 1);  // Maximizing

    // After sorting, the moves should be sorted by the values in dynamic_weights
    // in descending order (since we're maximizing).
    if (possibleMoves.moves[0][1] != 3 ||  // Move with the highest weight (0, 3) -> 50
        possibleMoves.moves[1][1] != 4 ||  // Second highest weight (0, 4) -> 40
        possibleMoves.moves[2][1] != 1 ||  // Third highest weight (0, 1) -> 30
        possibleMoves.moves[3][1] != 0) {  // Lowest weight (0, 0) -> 10
        return 1;  // Test failed
    }

    // Test case 2: Minimize
    sort_moves(board, &possibleMoves, dynamic_weights, &scores, 0);  // Minimizing

    // After sorting, the moves should be sorted by the values in dynamic_weights
    // in ascending order (since we're minimizing).
    if (possibleMoves.moves[0][1] != 0 ||  // Move with the lowest weight (0, 0) -> 10
        possibleMoves.moves[1][1] != 1 ||  // Second lowest weight (0, 1) -> 30
        possibleMoves.moves[2][1] != 4 ||  // Third lowest weight (0, 4) -> 40
        possibleMoves.moves[3][1] != 3) {  // Highest weight (0, 3) -> 50
        return 1;  // Test failed
    }

    // All tests passed
    return 1;
}

// Fonction de test pour update_scores
int test_update_scores() {
    int mat[7][9] = { // Matrice initiale (toutes les cases sont libres, représentées par des 0)
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    // Poids dynamiques pour chaque position sur la grille
    int dynamic_weights[7][9] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    // Initialiser les scores des joueurs
    Scores scores = {0, 0};

    // Appel de la fonction avec les paramètres de test
    update_scores(mat, 2, 3, &scores, 1, dynamic_weights);  // Test avec Player 1 qui maximise

    // Vérification des résultats
    if (scores.score_p1 > 0 && scores.score_p2 == 0) {
        printf("Test réussi : Player 1 a été correctement récompensé.\n");
    } else {
        printf("Test échoué : Les scores ne sont pas corrects pour Player 1.\n");
        return 0;
    }

    // Appel de la fonction pour Player 2 qui minimise
    update_scores(mat, 5, 6, &scores, 0, dynamic_weights);  // Test avec Player 2 qui minimise

    // Vérification des résultats
    if (scores.score_p2 > 0) {
        printf("Test réussi : Player 2 a été correctement récompensé.\n");
    } else {
        printf("Test échoué : Les scores ne sont pas corrects pour Player 2.\n");
        return 0;
    }

    return 1;  // Le test est réussi
}

