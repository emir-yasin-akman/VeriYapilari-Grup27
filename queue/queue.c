#include <stdlib.h>
#include "queue.h"

// Kuyrugu baslat
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if (q) {
        q->front = q->rear = NULL;
    }
    return q;
}

// Kuyruga eleman ekle (Dinamik bellek ayirma)
void enqueue(Queue* q, Node* node) {
    if (!q || !node) return;

    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (!newNode) return; // Bellek dolulugu kontrolu

    newNode->data = node;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

// Kuyruktan eleman cikar ve bellegi temizle
Node* dequeue(Queue* q) {
    if (!q || q->front == NULL) return NULL;

    QueueNode* temp = q->front;
    Node* nodeData = temp->data;

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp); // Sadece kuyruk dugumunu temizle, veriyi (Node) koru
    return nodeData;
}

int isEmpty(Queue* q) {
    return (q == NULL || q->front == NULL);
}

// Opsiyonel: Kuyruk tamamen bittiginde temizlik
void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}