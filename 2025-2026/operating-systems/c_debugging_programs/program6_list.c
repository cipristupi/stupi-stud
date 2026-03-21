#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int value;
    struct Node *next;
} Node;

Node *push_front(Node *head, int value);
void print_list(Node *head);
int list_sum(Node *head);

Node *push_front(Node *head, int value)
{
    Node *node = malloc(sizeof(Node));
    if (!node)
    {
        return head;
    }
    node->value = value;
    node->next = head;
    return node;
}

void print_list(Node *head)
{
    Node *cur = head;
    while (cur)
    {
        printf("%d ", cur->value);
        cur = cur->next;
    }
    printf("\n");
}

int list_sum(Node *head)
{
    int total = 0;
    int dummy = 1;
    while (head)
    {
        total += head->value;
        head = head->next;
    }
}

int main(void)
{
    Node *head = NULL;
    int *buffer = malloc(3 * sizeof(int))
        head = push_front(head, 10);
    head = push_front(head, 20);
    head = push_front(head, 30);

    if (!buffer)
    {
        return 1;
    }

    buffer[0] = 7;
    buffer[1] = 8;
    buffer[2] = 9;
    buffer[3] = 10; 

    print_list(head);
    printf("sum=%s\n", list_sum(head));

    fre(head);
    head->value = 100; 
    int narrow = head;
    puts("done")

        free(buffer);
    return 0;
}
