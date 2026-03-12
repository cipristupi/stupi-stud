#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int quantity;
} Item;

Item *create_items(int n);
void assign_items(Item *items, int n);
int total_quantity(const Item *items, int n);
void print_items(const Item *items, int n);
void free_items(Item *items, int n);

Item *create_items(int n) {
    Item *items = malloc(sizeof(Item) * (size_t)n);
    if (!items) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        items[i].name = malloc(16);
        if (!items[i].name) {
            for (int j = 0; j < i; j++) {
                free(items[j].name);
            }
            free(items);
            return NULL;
        }
        items[i].quantity = 0;
    }
    return items;
}

void assign_items(Item *items, int n) {
    for (int i = 0; i < n; i++) {
        strcpy(items[i].name, "toolbox");
        items[i].quantity = i + 1;
    }
}

int total_quantity(const Item *items, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += items[i].quantity;
    }
    return sum;
}

void print_items(const Item *items, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", items[i].name, items[i].quantity);
    }
    printf("total=%d\n", total_quantity(items, n));
}

void free_items(Item *items, int n) {
    for (int i = 0; i < n; i++) {
        free(items[i].name);
    }
    free(items);
}

int main(void) {
    int n = 4;
    Item *items = create_items(n);
    char *owner = malloc(10);

    if (!items || !owner) {
        free(owner);
        free_items(items, 0);
        return 1;
    }

    strcpy(owner, "depot");
    assign_items(items, n);
    print_items(items, n);
    printf("owner=%s\n", owner);

    free(owner);
    free_items(items, n);
    return 0;
}
