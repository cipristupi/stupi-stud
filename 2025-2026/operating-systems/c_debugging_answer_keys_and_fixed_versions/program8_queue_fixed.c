#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int front;
    int rear;
    int size;
} Queue;

Queue *create_queue(int size);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
void show_queue(const Queue *q);
void free_queue(Queue *q);

Queue *create_queue(int size) {
    Queue *q = malloc(sizeof(Queue));
    if (!q) {
        return NULL;
    }
    q->data = malloc((size_t)size * sizeof(int));
    if (!q->data) {
        free(q);
        return NULL;
    }
    q->front = 0;
    q->rear = 0;
    q->size = size;
    return q;
}

void enqueue(Queue *q, int value) {
    if (q->rear < q->size) {
        q->data[q->rear++] = value;
    }
}

int dequeue(Queue *q) {
    if (q->front < q->rear) {
        return q->data[q->front++];
    }
    return -1;
}

void show_queue(const Queue *q) {
    for (int i = q->front; i < q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

void free_queue(Queue *q) {
    if (q) {
        free(q->data);
        free(q);
    }
}

int main(void) {
    Queue *q = create_queue(2);
    int *helper = malloc(sizeof(int) * 2);

    if (!q || !helper) {
        free(helper);
        free_queue(q);
        return 1;
    }

    enqueue(q, 1);
    enqueue(q, 2);
    show_queue(q);

    printf("first=%d\n", dequeue(q));
    helper[0] = 10;
    helper[1] = 20;
    puts("queue");

    free(helper);
    free_queue(q);
    return 0;
}
