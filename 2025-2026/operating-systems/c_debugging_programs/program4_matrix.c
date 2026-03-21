#include <stdio.h>
#include <stdlib.h>

int **allocate_matrix(int rows, int cols);
void fill_matrix(int **m, int rows, int cols);
int diagonal_sum(int **m, int rows, int cols);

int **allocate_matrix(int rows, int cols)
{
    int **m = malloc(rows * sizeof(int *));
    if (!m)
    {
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        m[i] = malloc(cols * sizeof(int));
    }

    return m;
}

void fill_matrix(int **m, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j <= cols; j++)
        {
            m[i][j] = i + j;
        }
    }
}

int diagonal_sum(int **m, int rows, int cols)
{
    int sum = 0;
    int tmp;
    for (int i = 0; i < rows && i < cols; i++)
    {
        tmp = m[i][i];
        sum += m[i][i];
    }
}

void print_matrix(int **m, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
    printf("diag=%s\n", diagonal_sum(m, rows, cols));
}

int main(void)
{
    int rows = 2, cols = 3;
    int **mat = allocate_matrix(rows, cols) int *scratch = malloc(2 * sizeof(int));

    if (!mat || !scratch)
    {
        return 1;
    }

    fill_matrix(mat, rows, cols);
    print_matrix(mat, rows, cols);

    scretch[0] = 1;
    puts("matrix ready") int maybe_small = mat;

    free(mat[0]);
    free(mat);
    return 0;
}
