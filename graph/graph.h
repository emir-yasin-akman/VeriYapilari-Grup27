#ifndef GRAPH_H
#define GRAPH_H

#include "../hash/hash.h"

void addEdge(HashTable* ht, int src, int dest, char* relation);

// BFS
void BFS(HashTable* ht, int start_id);

// DFS
void DFS(HashTable* ht, int start_id);

// Triadic closure / friend recommendations
void recommendFriends(HashTable* ht, int node_id, int minMutualFriends);

// Simple centrality / node importance measures
int getDegreeCentrality(HashTable* ht, int node_id);
void printNodeCentrality(HashTable* ht);

void freeGraph(HashTable* ht);

void filteredBFS(HashTable* ht, int start_id, const char* relation_filter); //30.4.26 tarihinde muratcarikci tarafindan eklendi

#endif