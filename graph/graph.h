#ifndef GRAPH_H
#define GRAPH_H

#include "../hash/hash.h"
#include "../trie/trie.h"

// Mevcut Fonksiyonlar
void addEdge(HashTable* ht, int src, int dest, char* relation, int isDirected); // isDirected eklendi
void BFS(HashTable* ht, int start_id);
void DFS(HashTable* ht, int start_id);
void recommendFriends(HashTable* ht, int node_id, int minMutualFriends);
int getDegreeCentrality(HashTable* ht, int node_id);
void printNodeCentrality(HashTable* ht);
void freeGraph(HashTable* ht);
void filteredBFS(HashTable* ht, int start_id, const char* relation_filter);
void findPhotosOfFriendsEvents(HashTable* ht, int start_user_id);
void generateSyntheticData(HashTable* ht, int userCount, int eventCount, int photoCount, int edgeCount);

// YENİ EKLENEN EKSİK ÖZELLİKLER (Faz 1 - Trie Entegrasyonu ve Faz 3 - Görselleştirme)
void indexGraphWithTrie(HashTable* ht, TrieNode* trieRoot);
void searchAndPrintNodesByPrefix(HashTable* ht, TrieNode* trieRoot, char* prefix);
void exportGraphToDOT(HashTable* ht, const char* filename);

#endif
