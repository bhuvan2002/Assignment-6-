#include <stdio.h>
#include <stdlib.h>

struct sparse_matrix {
    int MAX;
    int** data;
    int row;
    int col;
    int len;
};

struct sparse_matrix* create_sparse_matrix(int r, int c) {
    struct sparse_matrix* matrix = (struct sparse_matrix*)malloc(sizeof(struct sparse_matrix));
    matrix->MAX = 100;
    matrix->data = (int**)malloc(matrix->MAX * sizeof(int*));
    for (int i = 0; i < matrix->MAX; i++) {
        matrix->data[i] = (int*)malloc(3 * sizeof(int));
    }
    matrix->row = r;
    matrix->col = c;
    matrix->len = 0;
    return matrix;
}

void insert(struct sparse_matrix* matrix, int r, int c, int val) {
    if (r > matrix->row || c > matrix->col) {
        printf("Wrong entry\n");
    } else {
        matrix->data[matrix->len][0] = r;
        matrix->data[matrix->len][1] = c;
        matrix->data[matrix->len][2] = val;
        matrix->len++;
    }
}

struct sparse_matrix* add(struct sparse_matrix* a, struct sparse_matrix* b) {
    if (a->row != b->row || a->col != b->col) {
        printf("Matrices can't be added\n");
        return NULL;
    } else {
        int apos = 0;
        int bpos = 0;
        struct sparse_matrix* result = create_sparse_matrix(a->row, a->col);
        while (apos < a->len && bpos < b->len) {
            if (a->data[apos][0] > b->data[bpos][0] ||
                (a->data[apos][0] == b->data[bpos][0] && a->data[apos][1] > b->data[bpos][1])) {
                insert(result, b->data[bpos][0], b->data[bpos][1], b->data[bpos][2]);
                bpos++;
            } else if (a->data[apos][0] < b->data[bpos][0] ||
                       (a->data[apos][0] == b->data[bpos][0] && a->data[apos][1] < b->data[bpos][1])) {
                insert(result, a->data[apos][0], a->data[apos][1], a->data[apos][2]);
                apos++;
            } else {
                int addedval = a->data[apos][2] + b->data[bpos][2];
                if (addedval != 0) {
                    insert(result, a->data[apos][0], a->data[apos][1], addedval);
                }
                apos++;
                bpos++;
            }
        }
        while (apos < a->len) {
            insert(result, a->data[apos][0], a->data[apos][1], a->data[apos][2]);
            apos++;
        }
        while (bpos < b->len) {
            insert(result, b->data[bpos][0], b->data[bpos][1], b->data[bpos][2]);
            bpos++;
        }
        return result;
    }
}

struct sparse_matrix* transpose(struct sparse_matrix* matrix) {
    struct sparse_matrix* result = create_sparse_matrix(matrix->col, matrix->row);
    result->len = matrix->len;
    int* count = (int*)malloc((matrix->col + 1) * sizeof(int));
    for (int i = 1; i <= matrix->col; i++) {
        count[i] = 0;
    }
    for (int i = 0; i < matrix->len; i++) {
        count[matrix->data[i][1]]++;
    }
    int* index = (int*)malloc((matrix->col + 1) * sizeof(int));
    index[1] = 0;
    for (int i = 2; i <= matrix->col; i++) {
        index[i] = index[i - 1] + count[i - 1];
    }
    for (int i = 0; i < matrix->len; i++) {
        int rpos = index[matrix->data[i][1]]++;
        result->data[rpos][0] = matrix->data[i][1];
        result->data[rpos][1] = matrix->data[i][0];
        result->data[rpos][2] = matrix->data[i][2];
    }
    return result;
}

struct sparse_matrix* multiply(struct sparse_matrix* a, struct sparse_matrix* b) {
    if (a->col != b->row) {
        printf("Can't multiply, Invalid dimensions\n");
        return NULL;
    }
    b = transpose(b);
    int apos, bpos;
    struct sparse_matrix* result = create_sparse_matrix(a->row, b->row);
    for (apos = 0; apos < a->len; ) {
        int r = a->data[apos][0];
        for (bpos = 0; bpos < b->len; ) {
            int c = b->data[bpos][0];
            int tempa = apos;
            int tempb = bpos;
            int sum = 0;
            while (tempa < a->len && a->data[tempa][0] == r && tempb < b->len && b->data[tempb][0] == c) {
                if (a->data[tempa][1] < b->data[tempb][1]) {
                    tempa++;
                } else if (a->data[tempa][1] > b->data[tempb][1]) {
                    tempb++;
                } else {
                    sum += a->data[tempa][2] * b->data[tempb][2];
                    tempa++;
                    tempb++;
                }
            }
            if (sum != 0) {
                insert(result, r, c, sum);
            }
            while (bpos < b->len && b->data[bpos][0] == c) {
                bpos++;
            }
        }
        while (apos < a->len && a->data[apos][0] == r) {
            apos++;
        }
    }
    return result;
}

void print(struct sparse_matrix* matrix) {
    printf("Dimension: %dx%d\n", matrix->row, matrix->col);
    printf("Sparse Matrix:\nRow Column Value\n");
    for (int i = 0; i < matrix->len; i++) {
        printf("%d %d %d\n", matrix->data[i][0], matrix->data[i][1], matrix->data[i][2]);
    }
}

void free_sparse_matrix(struct sparse_matrix* matrix) {
    for (int i = 0; i < matrix->MAX; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

int main() {
    struct sparse_matrix* a = create_sparse_matrix(4, 4
