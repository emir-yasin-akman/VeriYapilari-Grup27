#ifndef QUEUE_H
#define QUEUE_H

#include "../models/node.h"

// Kuyruk elemanlari icin bagli liste yapisi
typedef struct QueueNode {
    Node* data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode *front, *rear;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, Node* node);
Node* dequeue(Queue* q);
int isEmpty(Queue* q);
void freeQueue(Queue* q);

#endif