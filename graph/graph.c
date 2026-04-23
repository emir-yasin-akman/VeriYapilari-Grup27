#include <stdlib.h>
#include <string.h>
#include "graph.h"

void addEdge(HashTable* ht, int src, int dest, char* relation) {
    Node* source = getNode(ht, src);

    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->target_id = dest;
    strcpy(newEdge->relation, relation);
    newEdge->next = source->edges;

    source->edges = newEdge;
}