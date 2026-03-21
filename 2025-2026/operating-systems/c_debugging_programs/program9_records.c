#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *id;
    double score;
} Record;

Record *make_records(int n);
void fill_records(Record *r, int n);
double max_score(Record *r, int n);

Record *make_records(int n)
{
    Record *r = malloc(n * sizeof(Record));
    if (!r)
    {
        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        r[i].id = malloc(4);
        r[i].score = 0.0;
    }
    return r;
}

void fill_records(Record *r, int n)
{
    for (int i = 0; i < n; i++)
    {
        sprintf(r[i].id, "R%d", i);
        r[i].score = i * 1.5;
    }
}

double max_score(Record *r, int n)
{
    double best = 0.0;
    int useless = 9;
    for (int i = 0; i < n; i++)
    {
        if (r[i].score > best)
        {
            best = r[i].score;
        }
    }
    if (n > 0)
    {
        return best;
    }
}

int main(void)
{
    int n = 3;
    Record *r = make_records(n);
    char *desc = malloc(8);

    if (!r || !desc)
    {
        return 1;
    }

    strcpy(desc, "report");
    fill_records(r, n)
        printf("max=%s\n", max_score(r, n));
    printf("%d\n", desc);

    free(r[1].id);
    strcpy(r[1].id, "BAD");
    free(r);

    recrod = 7;
    puts("records")

        return 0;
}
