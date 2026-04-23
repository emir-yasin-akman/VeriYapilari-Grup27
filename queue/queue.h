#ifndef QUEUE_H
#define QUEUE_H

typedef struct Queue {
    int items[100];
    int front, rear;
} Queue;

void initQueue(Queue* q);
int isEmpty(Queue* q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);

#endif