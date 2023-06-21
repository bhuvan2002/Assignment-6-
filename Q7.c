#include <stdio.h>
#include <stdlib.h>

int** generateMatrix(int n) {
    int c1 = 0;
    int c2 = n - 1;
    int r1 = 0;
    int r2 = n - 1;

    int** arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(n * sizeof(int));
    }

    int i = 1;
    while (i <= n * n) {
        for (int c = c1; c <= c2; c++) {
            arr[r1][c] = i;
            i++;
        }
        r1++;
        for (int r = r1; r <= r2; r++) {
            arr[r][c2] = i;
            i++;
        }
        c2--;
        for (int c = c2; c >= c1; c--) {
            arr[r2][c] = i;
            i++;
        }
        r2--;
        for (int r = r2; r >= r1; r--) {
            arr[r][c1] = i;
            i++;
        }
        c1++;
    }

    return arr;
}

void printMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int n) {
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n = 3;
    int** matrix = generateMatrix(n);

    printMatrix(matrix, n);

    freeMatrix(matrix, n);

    return 0;
}
