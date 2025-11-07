#include <stdio.h>
#include <stdbool.h>

#define N 8  // Change this for different sizes of the board

int board[N][N];

// Function to print the board
void printBoard() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Check if it is safe to place a queen at board[row][col]
bool isSafe(int row, int col) {
    int i, j;

    // Check this row on the left side
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check lower diagonal on the left side
    for (i = row, j = col; i < N && j >= 0; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

// Recursive utility function to solve N-Queens
bool solveNQueens(int col) {
    if (col >= N)  // All queens placed
        return true;

    for (int i = 0; i < N; i++) {
        if (isSafe(i, col)) {
            board[i][col] = 1;  // Place queen

            if (solveNQueens(col + 1))
                return true;

            board[i][col] = 0;  // Backtrack
        }
    }
    return false;  // No place for this queen
}

int main() {
    // Initialize board with 0s
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = 0;

    if (solveNQueens(0)) {
        printf("One solution of the %d-Queens problem:\n", N);
        printBoard();
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}