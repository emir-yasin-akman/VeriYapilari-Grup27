#include "queue.h"

void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->rear == 99) return;

    if (q->front == -1) q->front = 0;

    q->items[++q->rear] = value;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];

    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;

    return item;
}