#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "../queue/queue.h"

// İlişki ekleme fonksiyonu
void addEdge(HashTable* ht, int src, int dest, char* relation) {
    Node* source = getNode(ht, src);
    Node* destination = getNode(ht, dest);

    // Her iki düğümün de var olduğundan emin olalım
    if (!source || !destination) return;

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) return;

    newEdge->target_id = dest;
    strcpy(newEdge->relation, relation);
    strcpy(newEdge->date, "2026"); // Sabit tarih veya sistem saati eklenebilir

    // Yeni kenarı listenin başına ekle
    newEdge->next = source->edges;
    source->edges = newEdge;
}

// ---------- BFS (Breadth First Search) ----------
// Yeni dinamik Queue yapısına uygun hale getirildi
void BFS(HashTable* ht, int start_id) {
    int visited[TABLE_SIZE * 2] = {0}; // Basit bir ziyaret tablosu

    Queue* q = createQueue();
    Node* startNode = getNode(ht, start_id);

    if (!startNode) {
        free(q);
        return;
    }

    enqueue(q, startNode);
    visited[start_id % (TABLE_SIZE * 2)] = 1;

    printf("Starting BFS from Node %d:\n", start_id);

    while (!isEmpty(q)) {
        Node* current = dequeue(q);
        printf("Visited Node: %d (Type: %s)\n", current->id, current->type);

        Edge* edge = current->edges;
        while (edge != NULL) {
            if (!visited[edge->target_id % (TABLE_SIZE * 2)]) {
                Node* neighbor = getNode(ht, edge->target_id);
                if (neighbor) {
                    visited[edge->target_id % (TABLE_SIZE * 2)] = 1;
                    enqueue(q, neighbor);
                }
            }
            edge = edge->next;
        }
    }
    
    // Kuyruk yapısını bellekten temizle (İçindeki düğümleri değil, sadece kuyruk düğümlerini)
    while(!isEmpty(q)) dequeue(q);
    free(q);
}

// ---------- DFS (Depth First Search) ----------
void DFS_util(HashTable* ht, int id, int visited[]) {
    visited[id % (TABLE_SIZE * 2)] = 1;
    Node* node = getNode(ht, id);
    if (!node) return;

    printf("Visited Node: %d (Type: %s)\n", node->id, node->type);

    Edge* edge = node->edges;
    while (edge != NULL) {
        if (!visited[edge->target_id % (TABLE_SIZE * 2)]) {
            DFS_util(ht, edge->target_id, visited);
        }
        edge = edge->next;
    }
}

void DFS(HashTable* ht, int start_id) {
    int visited[TABLE_SIZE * 2] = {0};
    printf("Starting DFS from Node %d:\n", start_id);
    DFS_util(ht, start_id, visited);
}

// ---------- FREE GRAPH (Memory Management) ----------
void freeGraph(HashTable* ht) {
    if (!ht) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* currentNode = ht->table[i];
        
        while (currentNode != NULL) {
            // 1. Özellikleri temizle
            Property* currentProp = currentNode->properties;
            while (currentProp != NULL) {
                Property* nextProp = currentProp->next;
                free(currentProp);
                currentProp = nextProp;
            }

            // 2. İlişkileri temizle
            Edge* currentEdge = currentNode->edges;
            while (currentEdge != NULL) {
                Edge* nextEdge = currentEdge->next;
                free(currentEdge);
                currentEdge = nextEdge;
            }

            // 3. Düğümü temizle ve sonrakine geç
            Node* tempNode = currentNode;
            currentNode = currentNode->next; // Hash collision listesindeki sonraki düğüm
            free(tempNode);
        }
        ht->table[i] = NULL;
    }
}