#include <stdio.h>
#include <stdbool.h>

bool isMountainArray(int* arr, int arrSize) {
    if (arrSize < 3)
        return false;

    int flag = 0;
    int i;

    for (i = 1; i < arrSize; i++) {
        if (arr[i] <= arr[i - 1])
            break;
    }

    if (i == arrSize || i == 1)
        return false;

    for (; i < arrSize; i++) {
        if (arr[i] >= arr[i - 1])
            break;
    }

    return i == arrSize;
}

int main() {
    int arr[] = {2, 1};
    int arrSize = sizeof(arr) / sizeof(arr[0]);

    bool result = isMountainArray(arr, arrSize);
    printf(result ? "true\n" : "false\n");

    return 0;
}
