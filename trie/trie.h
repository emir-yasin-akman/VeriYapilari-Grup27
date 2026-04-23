#ifndef TRIE_H
#define TRIE_H

// 26 yerine 128 yaparak tum ASCII karakterleri destekliyoruz (Buyuk harf, rakam vs.)
#define TRIE_CHAR_SIZE 128

typedef struct TrieNode {
    struct TrieNode* children[TRIE_CHAR_SIZE];
    int isEnd;
} TrieNode;

TrieNode* createTrieNode();
void insertTrie(TrieNode* root, char* word);

#endif