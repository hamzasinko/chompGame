#ifndef TRAITEMENT_TEST_H
#define TRAITEMENT_TEST_H

// Function to test 'test_case_selectionnee_0'
// This function verifies if the cell (6, 8) in a 7x9 matrix is valid according to 'verifierValiditeCase'.
// Returns 1 if the test passes, 0 otherwise.
int test_case_selectionnee_0();

// Function to test 'test_case_selectionnee_1'
// This function checks if the cell (6, 8) in a 7x9 matrix is valid according to 'verifierValiditeCase'.
// Returns 1 if the test passes, 0 otherwise.
int test_case_selectionnee_1();

// Function to test 'test_compteur_cases_valides'
// This function checks if the 'compteurCasesValides' function correctly counts the number of valid cells around (5, 6) in the matrix.
// Returns 1 if the test passes, 0 otherwise.
int test_compteur_cases_valides();

// Function to test 'test_modifierMatriceAvecCasesValides'
// This function verifies if the 'modifierMatriceAvecCasesValides' function correctly updates the matrix around the cell (5, 6).
// Returns 1 if the test passes, 0 otherwise.
int test_modifierMatriceAvecCasesValides();

// Function to test 'test_verifier_validite_case_more_than_5'
int test_verifier_validite_case_more_than_5();

int test_verifierValiditeCaseAi();
int testGenererPossibleMoves();
// Test function for saisie_valide
int testSaisieValide();
// Fonction de test de la conversion
int verifie_conversion();

int test_traductionAI();

#endif // TRAITEMENT_TEST_H