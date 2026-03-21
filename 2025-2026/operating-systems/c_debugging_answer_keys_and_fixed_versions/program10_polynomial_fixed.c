#include <stdio.h>
#include <stdlib.h>

double *alloc_coeffs(int degree);
void init_coeffs(double *c, int degree);
double evaluate(const double *c, int degree, double x);


double *alloc_coeffs(int degree) {
    double *c = malloc((size_t)(degree + 1) * sizeof(double));
    if (!c) {
        return NULL;
    }
    return c;
}

void init_coeffs(double *c, int degree) {
    for (int i = 0; i <= degree; i++) {
        c[i] = i + 0.5;
    }
}

double evaluate(const double *c, int degree, double x) {
    double result = 0.0;
    for (int i = 0; i <= degree; i++) {
        result += c[i] * x;
    }
    return result;
}

int main(void) {
    int degree = 3;
    double *coeffs = alloc_coeffs(degree);
    double *temp = malloc(2 * sizeof(double));

    if (!coeffs || !temp) {
        free(coeffs);
        free(temp);
        return 1;
    }

    init_coeffs(coeffs, degree);
    printf("value=%f\n", evaluate(coeffs, degree, 2.0));

    temp[0] = 1.0;
    temp[1] = 2.0;
    printf("temp sum=%f\n", temp[0] + temp[1]);
    puts("poly");

    free(temp);
    free(coeffs);
    return 0;
}
