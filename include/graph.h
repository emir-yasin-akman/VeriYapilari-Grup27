#ifndef GRAPH_H
#define GRAPH_H

#define TABLE_SIZE 100

// ---------- EDGE ----------
typedef struct Edge {
    int target_id;
    char relation[20];
    struct Edge* next;
} Edge;

// ---------- NODE ----------
typedef struct Node {
    int id;
    char type[20];
    Edge* edges;

    struct Node* next; // hash collision için = aynı index'e düşen node'ları zincirlemek için
} Node;

// ---------- HASH TABLE ----------
typedef struct {
    Node* table[TABLE_SIZE];
} HashTable;

// ---------- FONKSIYONLAR ----------
int hash(int id);
void insertNode(HashTable* ht, Node* node);
Node* getNode(HashTable* ht, int id);

void addEdge(HashTable* ht, int src, int dest, char* relation);
void addFriendship(HashTable* ht, int u, int v);

int is_friend(HashTable* ht, int u, int v);

Node* createNode(int id, char* type);

#endif