#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define ROWS 7
#define COLS 9

//Check if someone made the gameover move
bool checkWin(int board[ROWS][COLS]) {
    return board[0][0] == 1;
}

// Change matrix state after a move
void changeState(int board[ROWS][COLS], int m, int n) {
    for (int i = m; i < ROWS; i++) {
        for (int j = n; j < COLS; j++) {
            board[i][j] = 1;  // Utilise -1 pour représenter une case supprimée
        }
    }
}

// Reset matrix after a move
void revert(int src[ROWS][COLS], int dest[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// CHeck if move is valid
bool validMove(int board[ROWS][COLS], int m, int n) {
    int count = 0;
    for (int i = m; i < ROWS; i++) {
        for (int j = n; j < COLS; j++) {
            if (board[i][j] == 0) {
                count++;
            }
        }
    }
    return count <= 5;
}

//SImple evaluation algorithm based on cells distances to (0;0)
int evaluateBoard(int board[ROWS][COLS]) {
    int score = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                score += (i + j);  // Sum of cells distances to (0, 0)
            }
        }
    }
    return score;
}

// Algorithme Minimax avec élagage alpha-bêta
int minimax(int board[ROWS][COLS], bool is_max, int alpha, int beta, int depth) {
    if (checkWin(board)) {  //Does AI lost?
        return is_max ? 1000 : -1000; //Invert gains and losses since modifing gameover conditions didn't work
    }

    if (depth == 0) {  // Limiter la profondeur pour éviter trop de calculs
        return evaluateBoard(board);  //Return a simple evaluation score 
    }

    int b[ROWS][COLS];
    revert(board, b);

    if (is_max) {  //AI try to maximize score
        int best_score = -1000000;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == 0 && validMove(board, i, j)) {  // Limiter à 5 cases
                    changeState(board, i, j);
                    int score = minimax(board, false, alpha, beta, depth - 1);  //RUn player's turn
                    revert(b, board);
                    if (score > best_score) {
                        best_score = score;
                        alpha = (alpha > best_score) ? alpha : best_score;
                    }
                    if (alpha >= beta) {
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    } else {  //Algorithm try to minimize score
        int best_score = 1000000;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == 0 && validMove(board, i, j)) {  //Cap to 5 cells
                    changeState(board, i, j);
                    int score = minimax(board, true, alpha, beta, depth - 1);  //RUn the AI
                    revert(b, board);
                    if (score < best_score) {
                        best_score = score;
                        beta = (beta < best_score) ? beta : best_score;
                    }
                    if (alpha >= beta) {
                        return best_score;
                    }
                }
            }
        }
        return best_score;
    }
}

// IA chose best move with minimax algorithm
void aiMove(int board[ROWS][COLS], char *decision) {
    int best_score = -1000000;
    int best_move[2] = {0, 0};
    int b[ROWS][COLS];
    revert(board, b);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0 && validMove(board, i, j)) {  //Cap to 5 cells
                changeState(board, i, j);
                int score = minimax(board, false, -1000000, 1000000, 3);  // MAx recursion depth of 5
                revert(b, board);
                if (score > best_score) {
                    best_score = score;
                    best_move[0] = i;
                    best_move[1] = j;
                }
            }
        }
    }

    //Format output as a1, b3, etc.
    snprintf(decision, 4, "%c%d", 'a' + best_move[1], best_move[0] + 1);
}