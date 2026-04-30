#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "graph.h"
#include "../queue/queue.h"

// İlişki ekleme fonksiyonu
void addEdge(HashTable* ht, int src, int dest, char* relation) {
    Node* source = getNode(ht, src);
    Node* destination = getNode(ht, dest);

    if (!source || !destination) return;

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) return;

    newEdge->target_id = dest;
    strcpy(newEdge->relation, relation);

    // Sistem tarihini ekle
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(newEdge->date, sizeof(newEdge->date), "%02d-%02d-%04d",
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    newEdge->next = source->edges;
    source->edges = newEdge;
}

// ---------- BFS ----------
void BFS(HashTable* ht, int start_id) {
    int* visited = (int*)calloc(TABLE_SIZE, sizeof(int));
    if (!visited) return;

    Queue* q = createQueue();
    Node* startNode = getNode(ht, start_id);

    if (!startNode) {
        freeQueue(q);
        free(visited);
        return;
    }

    enqueue(q, startNode);
    visited[hash(start_id)] = 1;

    printf("Starting BFS from Node %d:\n", start_id);

    while (!isEmpty(q)) {
        Node* current = dequeue(q);
        printf("Visited Node: %d (Type: %s)\n", current->id, current->type);

        Edge* edge = current->edges;
        while (edge != NULL) {
            if (!visited[hash(edge->target_id)]) {
                Node* neighbor = getNode(ht, edge->target_id);
                if (neighbor) {
                    visited[hash(edge->target_id)] = 1;
                    enqueue(q, neighbor);
                }
            }
            edge = edge->next;
        }
    }

    freeQueue(q);
    free(visited);
}
