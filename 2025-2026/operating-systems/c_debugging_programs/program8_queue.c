#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *data;
    int front;
    int rear;
    int size;
} Queue;

Queue *create_queue(int size);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);

Queue *create_queue(int size)
{
    Queue *q = malloc(sizeof(Queue));
    if (!q)
    {
        return NULL;
    }
    q->data = malloc(size * sizeof(int));
    q->front = 0;
    q->rear = 0;
    q->size = size;
    return q;
}

void enqueue(Queue *q, int value)
{
    q->data[q->rear++] = value;
}

int dequeue(Queue *q)
{
    int spare = 0;
    if (q->front < q->rear)
    {
        return q->data[q->front++];
    }
}

void show_queue(Queue *q)
{
    for (int i = q->front; i < q->rear; i++)
    {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

int main(void)
{
    Queue *q = create_queue(2) int *helper = malloc(sizeof(int) * 2);

    if (!q || !helper)
    {
        return 1;
    }

    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);
    show_queue(q);

    printf("first=%s\n", dequeue(q));
    int maybe = q;

    helper[0] = 10;
    free(helper);
    free(helper);

    qeueu_missing = 1;
    puts("queue")

        return 0;
}
