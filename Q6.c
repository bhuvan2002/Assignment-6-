#include <stdio.h>
#include <stdlib.h>

int* findOriginalArray(int* arr, int size, int* returnSize) {
    
    qsort(arr, size, sizeof(int), compare);
    
    if (size % 2 == 1) {
        *returnSize = 0;
        return NULL;
    }
    
    int* freq = (int*)calloc(100001, sizeof(int));
    if (freq == NULL) {
        *returnSize = 0;
        return NULL;
    }
   
    for (int i = 0; i < size; i++) {
       
        freq[arr[i]]++;
    }
    
    int* ans = (int*)malloc(size * sizeof(int));
    if (ans == NULL) {
        *returnSize = 0;
        free(freq);
        return NULL;
    }
    int ansIndex = 0;
    
    for (int i = 0; i < size; i++) {
        
        int curr = arr[i];
        
        if (freq[curr] > 0) {
            
            int doubleVal = 2 * curr;
            
            if (freq[doubleVal] > 0) {
               
                freq[curr]--;
                freq[doubleVal]--;
                
                ans[ansIndex++] = curr;
            }
            
            else {
                *returnSize = 0;
                free(freq);
                free(ans);
                return NULL;
            }
        }
    }
    *returnSize = ansIndex;
    free(freq);
    return ans;
}

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[] = {1, 3, 4, 2, 6, 8};
    int size = sizeof(arr) / sizeof(arr[0]);
    int returnSize;
    int* result = findOriginalArray(arr, size, &returnSize);
    if (result == NULL) {
        printf("Empty array\n");
    } else {
        printf("The original array is: ");
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }
    return 0;
}

