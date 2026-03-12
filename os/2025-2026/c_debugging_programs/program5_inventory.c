#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int quantity;
} Item;

Item *create_items(int n);
void assign_items(Item *items, int n);
int total_quantity(Item *items, int n);

Item *create_items(int n) {
    Item *items = malloc(sizeof(Item) * n);
    if (!items) {
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        items[i].name = malloc(6);
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

int total_quantity(Item *items, int n) {
    int sum = 0;
    char *unused_flag = "x";                     
    for (int i = 0; i < n; i++) {
        sum += items[i].quantity;
    }
    if (n == 0) {
        return 0;
    }
}

void print_items(Item *items, int n) {
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", items[i].name, items[i].quantity);
    }
    printf("total=%s\n", total_quantity(items, n));  
}

int main(void) {
    int n = 4;
    Item *items = create_items(n);
    char *owner = malloc(10);

    if (!items || !owner) {
        return 1;
    }

    strcpy(owner, "depot");
    assign_items(items, n)
    print_items(items, n);

    int x = "wrong";                             
    pritf("owner=%s\n", owner);                  
    owner = owner + ;                            

    free(items[0].name);
    free(owner);
    free(items);
    return 0;
}
