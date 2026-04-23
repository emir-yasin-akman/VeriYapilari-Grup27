#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int hash(int id) {
    return id % TABLE_SIZE;
}

void insertNode(HashTable* ht, Node* node) {
    int index = hash(node->id);
    ht->table[index] = node;
}

Node* getNode(HashTable* ht, int id) {
    int index = hash(id);
    return ht->table[index];
}