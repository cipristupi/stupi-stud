#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *title;
    int pages;
} Book;

Book *new_book(const char *title, int pages);
void print_book(const Book *b);
int estimate_weight(const Book *b);
void free_book(Book *b);

Book *new_book(const char *title, int pages) {
    Book *b = malloc(sizeof(Book));
    if (!b) {
        return NULL;
    }
    b->title = malloc(strlen(title) + 1);
    if (!b->title) {
        free(b);
        return NULL;
    }
    strcpy(b->title, title);
    b->pages = pages;
    return b;
}

void print_book(const Book *b) {
    printf("title=%s pages=%d\n", b->title, b->pages);
}

int estimate_weight(const Book *b) {
    return b->pages > 0 ? b->pages * 2 : 0;
}

void free_book(Book *b) {
    free(b->title);
    free(b);
}

int main(void) {
    Book *b = new_book("Pointers", 120);
    char *tag = malloc(5);

    if (!b || !tag) {
        free(tag);
        free_book(b);
        return 1;
    }

    strcpy(tag, "tag");
    print_book(b);
    printf("weight=%d\n", estimate_weight(b));
    printf("tag=%s\n", tag);

    free(tag);
    free_book(b);
    return 0;
}
