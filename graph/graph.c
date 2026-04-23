#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "../queue/queue.h"

void addEdge(HashTable* ht, int src, int dest, char* relation) {
    Node* source = getNode(ht, src);
    if (!source) return;

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->target_id = dest;
    strcpy(newEdge->relation, relation);
    strcpy(newEdge->date, "2026");

    newEdge->next = source->edges;
    source->edges = newEdge;
}

// ---------- BFS ----------
void BFS(HashTable* ht, int start_id) {
    int visited[100] = {0};

    Queue q;
    initQueue(&q);

    enqueue(&q, start_id);
    visited[start_id] = 1;

    while (!isEmpty(&q)) {
        int current = dequeue(&q);
        printf("Visited: %d\n", current);

        Node* node = getNode(ht, current);
        if (!node) continue;

        Edge* edge = node->edges;

        while (edge != NULL) {
            int neighbor = edge->target_id;

            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                enqueue(&q, neighbor);
            }

            edge = edge->next;
        }
    }
}

// ---------- DFS ----------
void DFS_util(HashTable* ht, int id, int visited[]) {
    visited[id] = 1;
    printf("Visited: %d\n", id);

    Node* node = getNode(ht, id);
    if (!node) return;

    Edge* edge = node->edges;

    while (edge != NULL) {
        if (!visited[edge->target_id]) {
            DFS_util(ht, edge->target_id, visited);
        }
        edge = edge->next;
    }
}

void DFS(HashTable* ht, int start_id) {
    int visited[100] = {0};
    DFS_util(ht, start_id, visited);
}

// FREE GRAPH

void freeGraph(HashTable* ht) {
    if (!ht) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* currentNode = ht->table[i];
        
        while (currentNode != NULL) {
            // 1. Düğümün özelliklerini (Properties) temizle
            Property* currentProp = currentNode->properties;
            while (currentProp != NULL) {
                Property* nextProp = currentProp->next;
                free(currentProp);
                currentProp = nextProp;
            }

            // 2. Düğümün ilişkilerini (Edges) temizle
            Edge* currentEdge = currentNode->edges;
            while (currentEdge != NULL) {
                Edge* nextEdge = currentEdge->next;
                free(currentEdge);
                currentEdge = nextEdge;
            }

            // 3. Düğümün kendisini temizle ve sonrakine geç
            Node* tempNode = currentNode;
            currentNode = currentNode->next; // Hash tablosundaki çakışma listesi
            free(tempNode);
        }
        ht->table[i] = NULL; // Güvenlik için işaretçiyi sıfırla
    }
}

