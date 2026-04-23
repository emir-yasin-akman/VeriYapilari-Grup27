#include <stdlib.h>
#include "trie.h"

TrieNode* createTrieNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if (node) {
        node->isEnd = 0;
        for (int i = 0; i < TRIE_CHAR_SIZE; i++)
            node->children[i] = NULL;
    }
    return node;
}

void insertTrie(TrieNode* root, char* word) {
    TrieNode* temp = root;

    for (int i = 0; word[i]; i++) {
        // Artik her karakteri kendi ASCII degeriyle indeksliyoruz
        unsigned char index = (unsigned char)word[i];

        if (!temp->children[index])
            temp->children[index] = createTrieNode();

        temp = temp->children[index];
    }
    temp->isEnd = 1;
}