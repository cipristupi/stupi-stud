#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *create_array(int n);
void fill_array(int *arr, int n);
int sum_array(const int *arr, int n);
void print_array(const int *arr, int n);

int *create_array(int n) {
    int *arr = malloc((size_t)n * sizeof(int));
    if (arr == NULL) {
        return NULL;
    }
    return arr;
}

void fill_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i * 2;
    }
}

int sum_array(const int *arr, int n) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    return total;
}

void print_array(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {
    int n = 5;
    int *data = create_array(n);
    char *label = malloc(16);

    if (data == NULL || label == NULL) {
        free(data);
        free(label);
        return 1;
    }

    strcpy(label, "numbers");
    fill_array(data, n);
    printf("%s: ", label);
    print_array(data, n);
    printf("sum = %d\n", sum_array(data, n));

    free(label);
    free(data);
    return 0;
}
