#ifndef GRAPH_H
#define GRAPH_H

#include "../models/node.h"
#include "../hash/hash.h"

// Graf Yapısı İçin Temel Fonksiyon Tanımlamaları
void addEdge(HashTable* ht, int src, int dest, char* relation);
void BFS(HashTable* ht, int start_id);
void DFS(HashTable* ht, int start_id);

// Faz 1: Filtrelenmiş BFS Fonksiyon Tanımı
void filteredBFS(HashTable* ht, int start_id, const char* relation_filter);

// Analiz ve Öneri Algoritmaları
void recommendFriends(HashTable* ht, int node_id, int minMutualFriends);
int getDegreeCentrality(HashTable* ht, int node_id);
void printNodeCentrality(HashTable* ht);

// Faz 2 & Faz 3: Çok Adımlı Sorgu, Veri Üretimi ve JSON Çıktısı
void findPhotosOfFriendsEvents(HashTable* ht, int start_user_id);
void generateSyntheticData(HashTable* ht, int userCount, int eventCount, int photoCount, int edgeCount);
void exportGraphToJSON(HashTable* ht, const char* filename);

// Bellek Yönetimi
void freeGraph(HashTable* ht);

#endif // GRAPH_H
