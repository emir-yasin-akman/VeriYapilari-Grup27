#ifndef HASH_H
#define HASH_H

#include "../models/node.h"

#define TABLE_SIZE 100

typedef struct HashTable {
    Node* table[TABLE_SIZE];
} HashTable;

int hash(int id);
void insertNode(HashTable* ht, Node* node);
Node* getNode(HashTable* ht, int id);

#endif