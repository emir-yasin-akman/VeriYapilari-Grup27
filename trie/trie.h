#ifndef TRIE_H
#define TRIE_H

typedef struct TrieNode {
    struct TrieNode* children[26];
    int isEnd;
} TrieNode;

TrieNode* createTrieNode();
void insertTrie(TrieNode* root, char* word);

#endif