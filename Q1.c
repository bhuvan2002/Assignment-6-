#include <stdio.h>
#include <stdlib.h>

int* diStringMatch(char* s, int* returnSize) {
    int length = strlen(s);
    int* arr = (int*)malloc((length + 1) * sizeof(int));
    
    int a = 0;
    int b = length;
    
    for (int i = 0; i < length; i++) {
        if (s[i] == 'D')
            arr[i] = b--;
        else
            arr[i] = a++;
    }
    
    arr[length] = a;
    
    *returnSize = length + 1;
    return arr;
}

int main() {
    int returnSize;
    int* arr = diStringMatch("IDID", &returnSize);
    
    printf("The resulting array is: ");
    for (int i = 0; i < returnSize; i++)
        printf("%d ", arr[i]);
    
    free(arr);
    
    return 0;
}
