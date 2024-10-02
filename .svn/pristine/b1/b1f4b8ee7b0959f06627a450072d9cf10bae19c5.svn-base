#include "ai.h"
#include "const.h"
#include "traitement.h"
#include "matrice.h"
#include <limits.h>
#include <string.h>
#include <omp.h>

#define MAX_TABLE_SIZE 1000

typedef struct {
    int board[7][9];
    int depth;
    int score;
} TranspositionEntry;

TranspositionEntry transposition_table[MAX_TABLE_SIZE];
int table_size = 0;

// Hash function to map board states to table indices
unsigned int hash_board(int board[7][9]) {
    unsigned int hash = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            hash = hash * 31 + board[i][j];
        }
    }
    return hash % MAX_TABLE_SIZE;
}


int evaluate_move(int board[7][9], int x, int y, int dynamic_weights[7][9], Scores *scores, PossibleMoves *possibleMoves, int isMaximizing) {
    int temp_board[7][9];
    memcpy(temp_board, board, sizeof(int) * 7 * 9);
    Scores temp_scores = *scores;

    update_scores(temp_board, x, y, &temp_scores, isMaximizing, dynamic_weights);

    return evaluate(&temp_scores, temp_board, dynamic_weights, possibleMoves, isMaximizing);
}

// Lookup in transposition table
int lookup_transposition_table(int board[7][9], int *score) {
    unsigned int hash = hash_board(board);
    for (int i = 0; i < table_size; i++) {
        if (memcmp(transposition_table[i].board, board, sizeof(int) * 7 * 9) == 0) {
            *score = transposition_table[i].score;
            return 1;
        }
    }
    return 0;
}

// Store result in transposition table
void store_transposition_table(int board[7][9], int score) {
    unsigned int hash = hash_board(board);
    if (table_size < MAX_TABLE_SIZE) {
        memcpy(transposition_table[table_size].board, board, sizeof(int) * 7 * 9);
        transposition_table[table_size].score = score;
        table_size++;
    }
}

void sort_moves(int board[7][9], PossibleMoves *possibleMoves, int dynamic_weights[7][9], Scores *scores, int isMaximizing) {
    int move_evaluations[possibleMoves->taille];
    
    for (int i = 0; i < possibleMoves->taille; i++) {
        int x = possibleMoves->moves[i][0];
        int y = possibleMoves->moves[i][1];
        move_evaluations[i] = evaluate_move(board, x, y, dynamic_weights, scores, possibleMoves, isMaximizing);
    }
    
    for (int i = 0; i < possibleMoves->taille - 1; i++) {
        for (int j = i + 1; j < possibleMoves->taille; j++) {
            if ((isMaximizing && move_evaluations[i] < move_evaluations[j]) ||
                (!isMaximizing && move_evaluations[i] > move_evaluations[j])) {
                int temp_move[2] = {possibleMoves->moves[i][0], possibleMoves->moves[i][1]};
                possibleMoves->moves[i][0] = possibleMoves->moves[j][0];
                possibleMoves->moves[i][1] = possibleMoves->moves[j][1];
                possibleMoves->moves[j][0] = temp_move[0];
                possibleMoves->moves[j][1] = temp_move[1];
                
                int temp_eval = move_evaluations[i];
                move_evaluations[i] = move_evaluations[j];
                move_evaluations[j] = temp_eval;
            }
        }
    }
}



void adjust_weights(int mat[7][9], int dynamic_weights[7][9]) {
    int remaining_squares = 0;

    // Count remaining squares
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (mat[i][j] == 0) {
                remaining_squares++;
            }
        }
    }

    // Default weight setup for final cases
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            dynamic_weights[i][j] = position_weights[i][j];
        }
    }

    // Scenario-based weight adjustments
    if (remaining_squares <= 10) {
        // Endgame scenario: favor center positions
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 9; j++) {
                if (i >= 2 && i <= 4 && j >= 3 && j <= 5) {
                    dynamic_weights[i][j] += 10; // Higher weight for center positions
                }
            }
        }
    } else if (remaining_squares <= 20) {
        // Intermediate endgame scenario: prioritize corners and edges
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 9; j++) {
                if ((i == 0 || i == 6 || j == 0 || j == 8) && mat[i][j] == 0) {
                    dynamic_weights[i][j] += 8; // Higher weight for edge positions
                }
            }
        }
    } else {
        // Regular game scenario: small weight adjustments based on remaining squares
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 9; j++) {
                if (mat[i][j] == 0) {
                    dynamic_weights[i][j] += (remaining_squares % 2 == 0) ? 2 : -2;
                }
            }
        }
    }

    // Special case handling: Prevent critical mistakes in final few moves
    if (remaining_squares <= 5) {
        dynamic_weights[3][4] += 20;
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 9; j++) {
                if (mat[i][j] == 0 && (i == 6 || j == 8)) {
                    dynamic_weights[i][j] += 5; // Boost edge weights
                }
            }
        }
    }

    // Heavy penalty for (0,0)
    dynamic_weights[0][0] -= 1000;
}


int is_power_of_2(int num) {
    // A number is a power of 2 if it is greater than 0 and its binary representation has exactly one bit set.
    return num > 0 && (num & (num - 1)) == 0;
}

// Function to update the scores based on the current move
void update_scores(int mat[7][9], int x, int y, Scores *scores, int isMaximizing,int dynamic_weights[7][9]) {
    int elim_squares = 0, i, j;
    int positional_value = dynamic_weights[x][y];

    // Iterate through the board to update the state and count eliminated squares
    for (i = x; i < 7 && elim_squares <= 5; i++) {
        if (mat[i][y] == 0) {
            for (j = y; j < 9 && elim_squares <= 5; j++) {
                if (mat[i][j] == 0) {
                    elim_squares++;
                    mat[i][j] = 1;
                }
            }
        }
    }

    int remaining_cases = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (mat[i][j] == 0) {
                remaining_cases++;
            }
        }
    }

    if (is_power_of_2(remaining_cases)) {
        // Penalize the current player if the remaining cases is a power of 2
        if (isMaximizing) {
            scores->score_p1 -= 10;  // Penalize Player 1
        } else {
            scores->score_p2 -= 10;  // Penalize Player 2
        }
    } else {
        // Reward the current player if it's not a power of 2
        if (isMaximizing) {
            scores->score_p1 += 15;
        } else {
            scores->score_p2 += 15;
        }
    }

    // Update the scores based on whether it's maximizing or minimizing player
    if (isMaximizing) {
        scores->score_p1 += positional_value ;  // Increase score for Player 1
    } else {
        scores->score_p2 += positional_value ;  // Increase score for Player 2
    }
}

// Function to undo the move and revert the scores
void undo_move(int mat[7][9], int prevMat[7][9], int x, int y, Scores *scores, int isMaximizing,int dynamic_weights[7][9]) {
    int elim_squares = 0, i, j;
    int positional_value = dynamic_weights[x][y];

    int remaining_cases = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (mat[i][j] == 0) {
                remaining_cases++;
            }
        }
    }

    if (is_power_of_2(remaining_cases)) {
        // Penalize the current player if the remaining cases is a power of 2
        if (isMaximizing) {
            scores->score_p1 += 10;  // Penalize Player 1
        } else {
            scores->score_p2 += 10;  // Penalize Player 2
        }
    } else {
        // Reward the current player if it's not a power of 2
        if (isMaximizing) {
            scores->score_p1 -= 15;
        } else {
            scores->score_p2 -= 15;
        }
    }

    // Iterate through the board to revert the state and count eliminated squares
    for (i = x; i < 7 && elim_squares <= 5; i++) {
        for (j = y; j < 9 && elim_squares <= 5; j++) {
            if (mat[i][j] != prevMat[i][j]) {
                elim_squares++;
                mat[i][j] = 0;
            }
        }
    }

    // Revert the scores based on whether it's maximizing or minimizing player
    if (isMaximizing) {
        scores->score_p1 -= positional_value;
    } else {
        scores->score_p2 -= positional_value;
    }
}

// Function to evaluate the current score difference
int evaluate(Scores *scores, int board[7][9], int dynamic_weights[7][9], PossibleMoves *possibleMoves, int isMaximizing) {
    int eval = scores->score_p1 - scores->score_p2;
    int valid_moves = possibleMoves->taille;

    // Base evaluation based on current scores
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                // Dynamic weights influence the evaluation
                if (isMaximizing) {
                    eval += dynamic_weights[i][j]; // Favor Player 1
                } else {
                    eval -= dynamic_weights[i][j]; // Favor Player 2
                }
            }
        }
    }

    // Prioritize remaining move possibilities
    if (isMaximizing) {
        eval += valid_moves * 10;  // Favor Player 1 having more future moves
        eval -= (20 - valid_moves) * 10;  // Penalize Player 2's reduced moves
    } else {
        eval += valid_moves * 10;  // Favor Player 2 having more future moves
        eval -= (20 - valid_moves) * 10;  // Penalize Player 1's reduced moves
    }

    // New heuristic: Consider positional control
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                // Penalize leaving the AI in vulnerable corners
                if ((i == 0 || i == 6) && (j == 0 || j == 8)) {
                    eval -= isMaximizing ? 15 : 10;
                }
            }
        }
    }

    // Penalize isolated squares in late-game
    int remaining_squares = 0;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == 0) {
                remaining_squares++;
            }
        }
    }
    if (remaining_squares <= 5) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == 0) {
                    eval -= 10; // Penalize leaving isolated squares
                }
            }
        }
    }

    if (isMaximizing) {
        // Penalize if the opponent will have a strong response
        eval -= remaining_squares * 5;
    } else {
        // Reward if the opponent has fewer strong responses
        eval += remaining_squares * 5;
    }

    return eval;
}

// Minimax function with alpha-beta pruning
int minimax_with_alpha_beta(int board[7][9], int depth, int alpha, int beta, 
    int isMaximizing, Scores *scores, int prev_board[7][9]) {
    
    PossibleMoves possibleMoves;
    genererPossibleMoves(board, &possibleMoves);

    int dynamic_weights[7][9];
    adjust_weights(board, dynamic_weights);

    int transposition_score;
    if (lookup_transposition_table(board, &transposition_score)) {
        return transposition_score;
    }

    // Base case: return the evaluation of the board
    if (depth == 0 || board[0][0] == 1) {
        int eval = evaluate(scores, board, dynamic_weights, &possibleMoves, isMaximizing);
        store_transposition_table(board, eval);
        return eval;
    }

    if (isMaximizing) {
        int maxEval = INT_MIN;
        #pragma omp parallel for reduction(max:maxEval)
        for (int i = 0; i < possibleMoves.taille; i++) {
            int x = possibleMoves.moves[i][0];
            int y = possibleMoves.moves[i][1];
            int temp_board[7][9];

            // Copy the current board into temp_board before making a move
            memcpy(temp_board, board, sizeof(int) * 7 * 9);
            update_scores(temp_board, x, y, scores, 1, dynamic_weights);  // Player 1 makes the move

            // Recursively call minimax with the new board state
            int eval = minimax_with_alpha_beta(temp_board, depth - 1, alpha, beta, 0, scores, board);

            // Undo the move (reset board and scores)
            undo_move(temp_board, board, x, y, scores, 1, dynamic_weights);

            maxEval = (eval > maxEval) ? eval : maxEval;  // Maximize the evaluation
            alpha = (alpha > eval) ? alpha : eval;  // Update alpha
            if (beta <= alpha) {
                break;  // Alpha-beta pruning
            }
        }
        store_transposition_table(board, maxEval);
        return maxEval;

    } else {
        int minEval = INT_MAX;
        #pragma omp parallel for reduction(min:minEval)

        for (int i = 0; i < possibleMoves.taille; i++) {
            int x = possibleMoves.moves[i][0];
            int y = possibleMoves.moves[i][1];
            int temp_board[7][9];

            // Copy the current board into temp_board before making a move
            memcpy(temp_board, board, sizeof(int) * 7 * 9);
            update_scores(temp_board, x, y, scores, 0, dynamic_weights);  // Player 2 makes the move

            // Recursively call minimax with the new board state
            int eval = minimax_with_alpha_beta(temp_board, depth - 1, alpha, beta, 1, scores, board);

            // Undo the move (reset board and scores)
            undo_move(temp_board, board, x, y, scores, 0,dynamic_weights);

            minEval = (eval < minEval) ? eval : minEval;  // Minimize the evaluation
            beta = (beta < eval) ? beta : eval;  // Update beta
            if (beta <= alpha) {
                break;  // Alpha-beta pruning
            }
        }
        store_transposition_table(board, minEval);
        return minEval;
    }
}

// Function to find the best move using minimax with alpha-beta pruning
int find_best_move(int board[7][9], int depth, int indexe[2], int isMaximizing, Scores* scores, int prev_board[7][9]) {
    if (board[0][0] == 1)
        return 0;

    int dynamic_weights[7][9];
    adjust_weights(board, dynamic_weights);
    PossibleMoves possibleMoves;
    genererPossibleMoves(board, &possibleMoves);

    sort_moves(board, &possibleMoves, dynamic_weights, scores, isMaximizing);

    int best_value = isMaximizing ? INT_MIN : INT_MAX;

    for (int i = 0; i < possibleMoves.taille; i++) {
        int x = possibleMoves.moves[i][0];
        int y = possibleMoves.moves[i][1];

        // Store the current board and make the move
        memcpy(prev_board, board, sizeof(int) * 7 * 9);
        update_scores(board, x, y, scores, isMaximizing ? 1 : 0,dynamic_weights); 

        // Run minimax for this move
        int move_value = minimax_with_alpha_beta(board, depth - 1, INT_MIN, INT_MAX, !isMaximizing, scores, prev_board);

        // Undo the move
        undo_move(board, prev_board, x, y, scores, isMaximizing ? 1 : 0,dynamic_weights);

        // Check if this is the best move so far
        if (isMaximizing && move_value > best_value) {
            best_value = move_value;
            indexe[0] = x;
            indexe[1] = y;
        } else if (!isMaximizing && move_value < best_value) {
            best_value = move_value;
            indexe[0] = x;
            indexe[1] = y;
        }
    }
    return 1;
}

void aiMoveV1Max(int board[7][9], char input[2], Scores *score){
    int prev_board[7][9],index[2];
    index[0]=-1;
    index[1]=-1;
    find_best_move(board,8,index,1,score,prev_board);
    traductionAI(input,index);
}

void aiMoveV1Min(int board[7][9], char input[2], Scores *score){
    int prev_board[7][9],index[2];
    index[0]=-1;
    index[1]=-1;
    find_best_move(board,8,index,0,score,prev_board);
    traductionAI(input,index);
}
