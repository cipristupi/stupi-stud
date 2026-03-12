#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *id;
    double score;
} Record;

Record *make_records(int n);
void fill_records(Record *r, int n);
double max_score(const Record *r, int n);
void free_records(Record *r, int n);

Record *make_records(int n) {
    Record *r = malloc((size_t)n * sizeof(Record));
    if (!r) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        r[i].id = malloc(16);
        if (!r[i].id) {
            for (int j = 0; j < i; j++) {
                free(r[j].id);
            }
            free(r);
            return NULL;
        }
        r[i].score = 0.0;
    }
    return r;
}

void fill_records(Record *r, int n) {
    for (int i = 0; i < n; i++) {
        snprintf(r[i].id, 16, "R%d", i);
        r[i].score = i * 1.5;
    }
}

double max_score(const Record *r, int n) {
    double best = 0.0;
    for (int i = 0; i < n; i++) {
        if (r[i].score > best) {
            best = r[i].score;
        }
    }
    return best;
}

void free_records(Record *r, int n) {
    for (int i = 0; i < n; i++) {
        free(r[i].id);
    }
    free(r);
}

int main(void) {
    int n = 3;
    Record *r = make_records(n);
    char *desc = malloc(8);

    if (!r || !desc) {
        free(desc);
        free_records(r, 0);
        return 1;
    }

    strcpy(desc, "report");
    fill_records(r, n);
    printf("max=%.1f\n", max_score(r, n));
    printf("%s\n", desc);
    puts("records");

    free(desc);
    free_records(r, n);
    return 0;
}
