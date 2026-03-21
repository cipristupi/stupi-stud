#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node *push_front(Node *head, int value);
void print_list(const Node *head);
int list_sum(const Node *head);
void free_list(Node *head);

Node *push_front(Node *head, int value) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return head;
    }
    node->value = value;
    node->next = head;
    return node;
}

void print_list(const Node *head) {
    const Node *cur = head;
    while (cur) {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}

int list_sum(const Node *head) {
    int total = 0;
    while (head) {
        total += head->value;
        head = head->next;
    }
    return total;
}

void free_list(Node *head) {
    while (head) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void) {
    Node *head = NULL;
    int *buffer = malloc(3 * sizeof(int));

    head = push_front(head, 10);
    head = push_front(head, 20);
    head = push_front(head, 30);

    if (!buffer) {
        free_list(head);
        return 1;
    }

    buffer[0] = 7;
    buffer[1] = 8;
    buffer[2] = 9;

    print_list(head);
    printf("sum=%d\n", list_sum(head));
    puts("done");

    free(buffer);
    free_list(head);
    return 0;
}
