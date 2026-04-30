#include <stdlib.h>
#include "hash.h"

// Negatif ID degerlerine karsi mutlak deger kontrolu
int hash(int id) {
    return (id < 0 ? -id : id) % TABLE_SIZE;
}

void insertNode(HashTable* ht, Node* node) {
    if (!ht || !node) return;

    // Veri tutarliligi: Bu ID zaten var mi kontrol et
    if (getNode(ht, node->id) != NULL) {
        return; 
    }

    int index = hash(node->id);

    // Chaining: Yeni dugumu ilgili indeksteki listenin basina ekle
    node->next = ht->table[index];
    ht->table[index] = node;
}

Node* getNode(HashTable* ht, int id) {
    if (!ht) return NULL;

    int index = hash(id);
    Node* temp = ht->table[index];

    // Indeksteki bagli listeyi tara
    while (temp != NULL) {
        if (temp->id == id)
            return temp;
        temp = temp->next;
    }
    return NULL;
}