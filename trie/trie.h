#ifndef TRIE_H
#define TRIE_H

#define TRIE_CHAR_SIZE 128

typedef struct TrieNode {
    struct TrieNode* children[TRIE_CHAR_SIZE];
    int isEnd;
} TrieNode;

TrieNode* createTrieNode();
void insertTrie(TrieNode* root, char* word);
int searchTrie(TrieNode* root, char* word);

#endif
