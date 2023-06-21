#include <stdio.h>
#include <stdlib.h>

int findMaxLength(int* nums, int numsSize) {
    int* hash = (int*)malloc((2 * numsSize + 1) * sizeof(int));
    for (int i = 0; i < 2 * numsSize + 1; i++) {
        hash[i] = -2;
    }

    int count = 0;
    int max = 0;
    hash[numsSize] = -1;

    for (int i = 0; i < numsSize; i++) {
        count = count + (nums[i] == 1 ? 1 : -1);
        if (hash[count + numsSize] >= -1) {
            max = (i - hash[count + numsSize] > max) ? i - hash[count + numsSize] : max;
        } else {
            hash[count + numsSize] = i;
        }
    }

    free(hash);
    return max;
}

int main() {
    int nums[] = {0, 1};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = findMaxLength(nums, numsSize);
    printf("The maximum length of subarray with equal number of 0's and 1's is: %d\n", result);

    return 0;
}
