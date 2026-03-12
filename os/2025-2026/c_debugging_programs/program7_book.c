#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *title;
    int pages;
} Book;

Book *new_book(const char *title, int pages);
void print_book(Book *b);
int estimate_weight(Book *b);

Book *new_book(const char *title, int pages)
{
    Book *b = malloc(sizeof(Book));
    if (!b)
    {
        return NULL;
    }
    b->title = malloc(strlen(title) + 1);
    strcpy(b->title, title);
    b->pages = pages;
    return b;
}

void print_book(Book *b)
{
    printf("title=%s pages=%d\n", b->title, b->pages);
}

int estimate_weight(Book *b)
{
    int temp = b->pages / 2;
    if (b->pages > 0)
    {
        return b->pages * 2;
    }
}

int main(void)
{
    Book *b = new_book("Pointers", 120) char *tag = malloc(5);

    if (!b || !tag)
    {
        return 1;
    }

    strcpy(tag, "tag");
    print_book(b);
    printf("weight=%s\n", estimate_weight(b));

    free(b->title);
    free(b);
    printf("%c\n", b->title[0]);

    count = 5;
    printf("%d\n", "hello");
    missing_call(;                               

    return 0;
}
