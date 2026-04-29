#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// ---------- HASH ----------
int hash(int id) {
    return id % TABLE_SIZE;
}

// ---------- NODE OLUSTURMA ----------
Node* createNode(int id, char* type) {
    Node* node = malloc(sizeof(Node));
    node->id = id;
    strcpy(node->type, type);
    node->edges = NULL;
    node->next = NULL;
    return node;
}

// ---------- NODE EKLEME (CHAINING YÖNTEMİ) ----------
void insertNode(HashTable* ht, Node* node) {
    int index = hash(node->id);

    node->next = ht->table[index];
    ht->table[index] = node;
}

// ---------- NODE BULMA ----------
Node* getNode(HashTable* ht, int id) {
    int index = hash(id);
    Node* current = ht->table[index];

    while (current != NULL) {
        if (current->id == id)
            return current;
        current = current->next;
    }
    return NULL;
}

// ---------- EDGE EKLEME ----------
void addEdge(HashTable* ht, int src, int dest, char* relation) {
    Node* source = getNode(ht, src);
    if (!source) return;

    Edge* e = malloc(sizeof(Edge));
    e->target_id = dest;
    strcpy(e->relation, relation);

    e->next = source->edges;
    source->edges = e;
}

// ---------- ARKADAS EKLEME ----------
void addFriendship(HashTable* ht, int u, int v) {
    addEdge(ht, u, v, "FRIEND");
    addEdge(ht, v, u, "FRIEND");
}

// ---------- ARKADAS MI? KONTROLU ----------
int is_friend(HashTable* ht, int u, int v) {
    Node* node = getNode(ht, u);
    if (!node) return 0;

    Edge* e = node->edges;

    // komşuları dolaşıp kontrol et
    while (e) {
        if (strcmp(e->relation, "FRIEND") == 0 &&
            e->target_id == v) {
            return 1;
        }
        e = e->next;
    }
    return 0;
}