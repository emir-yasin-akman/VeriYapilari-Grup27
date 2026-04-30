#ifndef GRAPH_H
#define GRAPH_H

#include "../hash/hash.h"

void addEdge(HashTable* ht, int src, int dest, char* relation);

// BFS
void BFS(HashTable* ht, int start_id);

// DFS
void DFS(HashTable* ht, int start_id);

void freeGraph(HashTable* ht);

#endif