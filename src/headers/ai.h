#ifndef AI_H
#define AI_H
#include "traitement.h"
typedef struct {
    int score_p1;
    int score_p2;
} Scores;

void update_scores(int board[7][9], int x, int y, Scores *scores, int isMaximizing,int dynamic_weights[7][9]);
void undo_move(int mat[7][9], int prevMat[7][9], int x, int y, Scores *scores, int isMaximizing,int dynamic_weights[7][9]);
int evaluate(Scores *scores, int board[7][9], int dynamic_weights[7][9], PossibleMoves *possibleMoves, int isMaximizing);
int minimax_with_alpha_beta(int board[7][9], int depth, int alpha, int beta, 
    int isMaximizing, Scores *scores, 
    int prev_board[7][9]);
int find_best_move(int board[7][9], int depth, int indexe[2], int isMaximizing, Scores* scores, int prev_board[7][9]);
void aiMoveV1Max(int board[7][9], char input[2], Scores *score);
void aiMoveV1Min(int board[7][9], char input[2], Scores *score);
void adjust_weights(int mat[7][9], int dynamic_weights[7][9]);
void sort_moves(int board[7][9], PossibleMoves *possibleMoves, int dynamic_weights[7][9], Scores *scores, int isMaximizing);

#endif