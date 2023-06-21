#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int minValue(int* A, int* B, int n) {
    qsort(A, n, sizeof(int), compare);
    qsort(B, n, sizeof(int), compare);

    int result = 0;
    for (int i = 0; i < n; i++) {
        result += A[i] * B[n - i - 1];
    }

    return result;
}

int main() {
    int A[] = {5, 3, 4, 2};
    int B[] = {4, 2, 2, 5};
    int n = sizeof(A) / sizeof(A[0]);

    int result = minValue(A, B, n);
    printf("The minimum product sum is: %d\n", result);

    return 0;
}
