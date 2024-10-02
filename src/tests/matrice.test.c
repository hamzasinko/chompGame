#include <stdio.h>
#include <string.h>
#include "../headers/matrice.h"

// Test function for remplissage
int test_remplissage() {
    // Initialize a 7x9 matrix with all values set to 0
    int matrice[7][9] = { 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0, 0, 0, 0} 
    };

    int mat[7][9], i, j;

    // Call the function to fill the matrix
    remplissage(mat);

    // Compare the contents of the original matrix with the modified matrix
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 9; j++) {
            if (matrice[i][j] != mat[i][j]) {
                // Return 0 if any discrepancy is found
                return 0;
            }
        }
    }

    // Return 1 if all values match
    return 1;
}

// Test function for affichage
int test_affichage() {
    // Initialize a 7x9 matrix with predefined values
    int mat[7][9] = {
        {0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 0, 0, 1}
    };

    // Save the original stdout
    FILE *original_stdout = stdout;

    // Redirect output to a file
    FILE *fp = freopen("test_output.txt", "w", stdout);
    if (fp == NULL) {
        // Print an error message if redirection fails
        perror("Failed to redirect stdout");
        return 0;
    }

    // Call the function to print the matrix
    affichage(mat);

    // Flush stdout to ensure all content is written
    fflush(stdout);
    fclose(fp);

    // Restore stdout back to the console (reopens stdout for terminal)
    freopen("/dev/tty", "w", stdout);

    // Re-open the file to read and compare its contents
    fp = fopen("test_output.txt", "r");
    if (fp == NULL) {
        // Print an error message if file opening fails
        perror("Failed to open output file");
        return 0;
    }

    // Read the file's content into a buffer
    char buffer[5000] = {0}; // Null-terminate the buffer
    size_t bytesRead = fread(buffer, sizeof(char), sizeof(buffer) - 1, fp);  // Leave space for null-terminator
    buffer[bytesRead] = '\0';  // Ensure null termination

    fclose(fp);

    // Check if the content matches the expected pattern
    if (strstr(buffer, "\e[0;37mA   B   C   D   E   F   G   H   I\e[0m") != NULL) {
        // Print success message if pattern is found
        printf("Test passed!\n");
    } else {
        // Print failure message if pattern is not found
        printf("Test failed!\n");
        return 0;
    }

    // Return 1 if the content matches the expected pattern
    return 1;
}
