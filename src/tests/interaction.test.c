#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../headers/traitement.h"
#include "../headers/matrice.h"
#include "../headers/interaction.h"
#include "../headers/const.h"
#include "../headers/network.h"

// Test function for coupPerdant
int test_coupPerdant() {
    // Test cases
    struct {
        char input[3]; // +1 for null terminator
        int expected;  // Expected result
    } tests[] = {
        {"a1", 1},   // Test case where input is exactly "a1"
        {"A1", 1},   // Test case where input is exactly "A1"
        {"b2", 0},   // Test case where input is not "a1" or "A1"
        {"A2", 0},   // Test case where input is not "a1" or "A1"
        {"a", 0},    // Test case where input length is not 2
        {"", 0}      // Test case where input is empty
    };

    int num_tests = sizeof(tests) / sizeof(tests[0]);
    int all_tests_passed = 1;

    for (int i = 0; i < num_tests; i++) {
        int actual = coupPerdant(tests[i].input);
        if (actual != tests[i].expected) {
            fprintf(stderr, "Test %d failed: expecting %d but got %d for input \"%s\"\n", 
                    i + 1, tests[i].expected, actual, tests[i].input);
            all_tests_passed = 0;
        }
    }

    return all_tests_passed;
}

int test_saisie() {
    char input[3];
    int index[2] = {-1, -1};

    // Simuler une saisie correcte "A1"
    strcpy(input, "A1");
    traduction(input, index); // Traduire la saisie en indices

    // Vérifier que l'indice correspond bien à la case A1 (colonne 0, ligne 0)
    if (index[0] == 0 && index[1] == 0) {
        return 1; // Le test est réussi
    } else {
        return 0; // Le test a échoué
    }
}

int test_miseAJourParReseau() {
    char input[2] = {'B', '2'}; // Simulate an input from the network
    int index[2];

    // Test case 1: Initial values are -1, so the loop should run
    index[0] = -1;
    index[1] = -1;
    miseAJourParReseau(input, index);

    // After the function call, index should no longer be -1
    if (index[0] != 1 || index[1] != 1) {
        return 0;  // Test failed
    }

    // Test case 2: When index values are already valid, the loop should not run
    index[0] = 5;
    index[1] = 6;
    miseAJourParReseau(input, index);

    // The values should remain unchanged
    if (index[0] != 5 || index[1] != 6) {
        return 0;  // Test failed
    }

    // All tests passed
    return 1;
}