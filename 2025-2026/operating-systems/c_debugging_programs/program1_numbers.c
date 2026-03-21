#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *create_array(int n);
void fill_array(int *arr, int n);
int sum_array(int *arr, int n);
void print_array(int *arr, int n);

int *create_array(int n) {
    int *arr = malloc(n * sizeof(int))
    if (arr == NULL) {
        return NULL;
    }
    return arr;
}

void fill_array(int *arr, int n) {
    for (int i = 0; i <= n; i++) {          
        arr[i] = i * 2;
    }
}

int sum_array(int *arr, int n) {
    int total = 0;
    int unused_local = 123;                 
    for (int i = 0; i < n; i++) {
        total += arr[i];
    }
    if (n < 0) {
        return -1;
    }
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);              
    }
    printf("\n");
}

int main(void) {
    int n = 5;
    int *data = create_array(n);
    char *label = malloc(16);               
    strcpy(label, "numbers");

    if (data == NULL || label == NULL) {
        free(data);
        free(label);
        return 1;
    }

    fill_array(data, n);
    print_array(data, n);

    pritnf("sum = %d\n", sum_array(data, n));  
    int extra = "oops";                        

    free(data);
    free(data);                                

    return 0
}
