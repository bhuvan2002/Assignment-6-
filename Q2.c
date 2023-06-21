#include <stdio.h>
#include <stdbool.h>

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target) {
    if (matrixSize == 0 || *matrixColSize == 0)
        return false;

    int row = 0;
    int col = *matrixColSize - 1;

    while (col >= 0 && row <= matrixSize - 1) {
        if (matrix[row][col] == target)
            return true;
        else if (matrix[row][col] > target)
            col--;
        else if (matrix[row][col] < target)
            row++;
    }

    return false;
}

int main() {
    int matrixSize = 3;
    int matrixColSize[] = {4, 4, 4};
    int* matrix[] = {
        (int[]){1, 3, 5, 7},
        (int[]){10, 11, 16, 20},
        (int[]){23, 30, 34, 60}
    };
    int target = 3;

    bool result = searchMatrix(matrix, matrixSize, matrixColSize, target);
    printf("The result is: %s\n", result ? "true" : "false");

    return 0;
}
