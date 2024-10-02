#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "./headers/matrice.h"
#include "./headers/traitement.h"
#include "./headers/interaction.h"
#include "./headers/ai.h"
#include "./headers/const.h"
#include "./tests/traitement.test.h"
#include "./tests/matrice.test.h"
#include "./tests/interaction.test.h"
#include "./tests/network.test.h"
#include "./tests/ai.test.h"

// Function to run a test and update failure and run counters
void run_test(int (*f)(), int *failures, int *runs) {
    if (!f()) {
        // Increment failures if the test function returns 0 (indicating failure)
        (*failures)++;
    }
    // Increment the count of tests run
    (*runs)++;
}

int main() {
    int test_count = 0;  // Total number of tests run
    int failures = 0;   // Count of failed tests

    // Run each test function and update counters
    run_test(test_case_selectionnee_0, &failures, &test_count);
    run_test(test_case_selectionnee_1, &failures, &test_count);
    run_test(test_compteur_cases_valides, &failures, &test_count);
    run_test(test_affichage, &failures, &test_count);
    run_test(test_remplissage, &failures, &test_count);
    run_test(test_modifierMatriceAvecCasesValides, &failures, &test_count);
    run_test(test_coupPerdant, &failures, &test_count);
    //run_test(test_verifier_validite_case_more_than_5, &failures, &test_count);
    //run_test(test_initClientSocket, &failures, &test_count);
    //run_test(test_accepterClient, &failures, &test_count);
    run_test(test_verifierValiditeCaseAi, &failures, &test_count);
    run_test(testGenererPossibleMoves, &failures, &test_count);
    run_test(testSaisieValide, &failures, &test_count);
    run_test(verifie_conversion, &failures, &test_count);
    run_test(test_saisie, &failures, &test_count);
    run_test(test_initServerSocket, &failures, &test_count);
    run_test(test_traductionAI, &failures, &test_count);
    run_test(test_miseAJourParReseau, &failures, &test_count);
    run_test(test_sort_moves, &failures, &test_count);
    run_test(test_update_scores, &failures, &test_count);

    // Print the results: number of failures and total number of tests
    printf("\n%d failures out of %d tests\n", failures, test_count);
    fflush(stdout);  // Ensure all output is flushed to stdout

    // Return the number of failures as the exit code
    return failures; 
}
