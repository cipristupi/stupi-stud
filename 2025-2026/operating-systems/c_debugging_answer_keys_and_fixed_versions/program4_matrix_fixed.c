#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int rows, int cols);
void fill_matrix(int **m, int rows, int cols);
int diagonal_sum(int **m, int rows, int cols);
void print_matrix(int **m, int rows, int cols);
void free_matrix(int **m, int rows);

int **allocate_matrix(int rows, int cols) {
    int **m = malloc((size_t)rows * sizeof(int *));
    if (!m) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        m[i] = malloc((size_t)cols * sizeof(int));
        if (!m[i]) {
            for (int j = 0; j < i; j++) {
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }

    return m;
}

void fill_matrix(int **m, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m[i][j] = i + j;
        }
    }
}

int diagonal_sum(int **m, int rows, int cols) {
    int sum = 0;
    for (int i = 0; i < rows && i < cols; i++) {
        sum += m[i][i];
    }
    return sum;
}

void print_matrix(int **m, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("diag=%d\n", diagonal_sum(m, rows, cols));
}

void free_matrix(int **m, int rows) {
    for (int i = 0; i < rows; i++) {
        free(m[i]);
    }
    free(m);
}

int main(void) {
    int rows = 2, cols = 3;
    int **mat = allocate_matrix(rows, cols);
    int *scratch = malloc(2 * sizeof(int));

    if (!mat || !scratch) {
        free(scratch);
        free_matrix(mat, rows);
        return 1;
    }

    fill_matrix(mat, rows, cols);
    print_matrix(mat, rows, cols);

    scratch[0] = 1;
    scratch[1] = 2;
    puts("matrix ready");

    free(scratch);
    free_matrix(mat, rows);
    return 0;
}
