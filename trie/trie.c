#include <stdlib.h>
#include "trie.h"

TrieNode* createTrieNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->isEnd = 0;

    for (int i = 0; i < 26; i++)
        node->children[i] = NULL;

    return node;
}

void insertTrie(TrieNode* root, char* word) {
    TrieNode* temp = root;

    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';

        if (!temp->children[index])
            temp->children[index] = createTrieNode();

        temp = temp->children[index];
    }

    temp->isEnd = 1;
}