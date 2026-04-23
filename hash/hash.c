#include <stdlib.h>
#include "hash.h"

int hash(int id) {
    // Negatif ID'lere karsi onlem
    return (id < 0 ? -id : id) % TABLE_SIZE;
}

void insertNode(HashTable* ht, Node* node) {
    // Oncelikle bu ID zaten var mi kontrol etmeliyiz (Veri tutarliligi)
    if (getNode(ht, node->id) != NULL) {
        return; // Veya bir hata mesaji dondurulebilir
    }

    int index = hash(node->id);
    // Chaining: Yeni dugumu listenin basina ekle
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