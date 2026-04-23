#include <stdlib.h>
#include "hash.h"

int hash(int id) {
    return id % TABLE_SIZE;
}

void insertNode(HashTable* ht, Node* node) {
    int index = hash(node->id);

    node->next = ht->table[index];
    ht->table[index] = node;
}

Node* getNode(HashTable* ht, int id) {
    int index = hash(id);
    Node* temp = ht->table[index];

    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}