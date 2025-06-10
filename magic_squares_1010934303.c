#include <stdio.h>

void solveMagicSquare(int square[3][3], int n) {
    int magicSum = (n * (n * n + 1)) / 2;

    // Identify missing values
    int missingRow = -1, missingCol = -1;

    for (int i = 0; i < n; i++) {
        int rowSum = 0, missingCount = 0;
        for (int j = 0; j < n; j++) {
            if (square[i][j] == 0) {
                missingRow = i;
                missingCol = j;
                missingCount++;
            } else {
                rowSum += square[i][j];
            }
        }
        // If there's exactly one missing value in the row, compute it
        if (missingCount == 1) {
            square[missingRow][missingCol] = magicSum - rowSum;
            return;
        }
    }
}

int main() {
    int magicSquare[3][3] = {
        {8, 1, 6},
        {3, 0, 7}, // Missing value at [1][1]
        {4, 9, 2}
    };

    int n = 3;
    solveMagicSquare(magicSquare, n);

    // Print completed magic square
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", magicSquare[i][j]);
        }
        printf("\n");
    }

    return 0;
}
