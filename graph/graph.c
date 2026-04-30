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

static int areConnected(HashTable* ht, int src_id, int dest_id) {
    Node* src = getNode(ht, src_id);
    if (!src) return 0;

    Edge* edge = src->edges;
    while (edge != NULL) {
        if (edge->target_id == dest_id)
            return 1;
        edge = edge->next;
    }
    return 0;
}

static void dfsUtil(HashTable* ht, Node* node, int* visited) {
    if (!node || !visited) return;

    printf("Visited Node: %d (Type: %s)\n", node->id, node->type);
    visited[hash(node->id)] = 1;

    Edge* edge = node->edges;
    while (edge != NULL) {
        Node* neighbor = getNode(ht, edge->target_id);
        if (neighbor && !visited[hash(neighbor->id)]) {
            dfsUtil(ht, neighbor, visited);
        }
        edge = edge->next;
    }
}

void DFS(HashTable* ht, int start_id) {
    int* visited = (int*)calloc(TABLE_SIZE, sizeof(int));
    if (!visited) return;

    Node* startNode = getNode(ht, start_id);
    if (!startNode) {
        free(visited);
        return;
    }

    printf("Starting DFS from Node %d:\n", start_id);
    dfsUtil(ht, startNode, visited);

    free(visited);
}

typedef struct {
    int node_id;
    int mutual_count;
} Recommendation;

void recommendFriends(HashTable* ht, int node_id, int minMutualFriends) {
    Node* node = getNode(ht, node_id);
    if (!node) return;

    Recommendation recommendations[TABLE_SIZE];
    int recCount = 0;

    Edge* edge = node->edges;
    while (edge != NULL) {
        Node* friendNode = getNode(ht, edge->target_id);
        if (friendNode) {
            Edge* fofEdge = friendNode->edges;
            while (fofEdge != NULL) {
                int candidateId = fofEdge->target_id;
                if (candidateId != node_id && !areConnected(ht, node_id, candidateId)) {
                    int found = 0;
                    for (int i = 0; i < recCount; i++) {
                        if (recommendations[i].node_id == candidateId) {
                            recommendations[i].mutual_count += 1;
                            found = 1;
                            break;
                        }
                    }
                    if (!found && recCount < TABLE_SIZE) {
                        recommendations[recCount].node_id = candidateId;
                        recommendations[recCount].mutual_count = 1;
                        recCount++;
                    }
                }
                fofEdge = fofEdge->next;
            }
        }
        edge = edge->next;
    }

    printf("Friend recommendations for Node %d:\n", node_id);
    if (recCount == 0) {
        printf("  No friend-of-friend suggestions found.\n");
        return;
    }

    for (int i = 0; i < recCount; i++) {
        if (recommendations[i].mutual_count >= minMutualFriends) {
            Node* candidate = getNode(ht, recommendations[i].node_id);
            char* name = candidate ? getProperty(candidate->properties, "name") : NULL;
            if (name) {
                printf("  - Node %d (%s): %d mutual friend%s\n",
                       recommendations[i].node_id,
                       name,
                       recommendations[i].mutual_count,
                       recommendations[i].mutual_count == 1 ? "" : "s");
            } else {
                printf("  - Node %d: %d mutual friend%s\n",
                       recommendations[i].node_id,
                       recommendations[i].mutual_count,
                       recommendations[i].mutual_count == 1 ? "" : "s");
            }
        }
    }
}

void freeGraph(HashTable* ht) {
    if (!ht) return;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* current = ht->table[i];
        while (current != NULL) {
            Node* nextNode = current->next;

            Property* prop = current->properties;
            while (prop != NULL) {
                Property* nextProp = prop->next;
                free(prop);
                prop = nextProp;
            }

            Edge* edge = current->edges;
            while (edge != NULL) {
                Edge* nextEdge = edge->next;
                free(edge);
                edge = nextEdge;
            }

            free(current);
            current = nextNode;
        }
        ht->table[i] = NULL;
    }
}
