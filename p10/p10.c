#include <stdio.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/resource.h>

#define MAX 10

void printSolution(int n, int board[MAX][MAX]);
bool solveNQueens(int n, int board[MAX][MAX], int col);
bool isSafe(int n, int board[MAX][MAX], int row, int col);

int main() {
    struct timeval tv1, tv2;
    struct rusage r_usage;
    int n;
    int board[MAX][MAX] = {0};

    printf("Enter the number of queens (N): ");
    scanf("%d", &n);

    gettimeofday(&tv1, NULL);
    bool solvable = solveNQueens(n, board, 0);
    gettimeofday(&tv2, NULL);

    if (solvable) {
        printf("Solution found for %d queens:\n", n);
        printSolution(n, board);
    } else {
        printf("No solution exists for %d queens.\n", n);
    }

    printf("Time taken by N-Queens algorithm: %ld microseconds\n", (tv2.tv_sec - tv1.tv_sec) * 1000000L + (tv2.tv_usec - tv1.tv_usec));
    getrusage(RUSAGE_SELF, &r_usage);
    printf("Memory used: %ld bytes\n", r_usage.ru_maxrss * 1024);

    return 0;
}

bool solveNQueens(int n, int board[MAX][MAX], int col) {
    if (col >= n) {
        return true;
    }

    for (int i = 0; i < n; i++) {
        if (isSafe(n, board, i, col)) {
            board[i][col] = 1;
            if (solveNQueens(n, board, col + 1)) {
                return true;
            }
            board[i][col] = 0; // backtrack
        }
    }

    return false;
}

bool isSafe(int n, int board[MAX][MAX], int row, int col) {
    for (int i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
        if (row - i >= 0 && board[row - i][col - i]) {
            return false;
        }
        if (row + i < n && board[row + i][col - i]) {
            return false;
        }
    }
    return true;
}

void printSolution(int n, int board[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

