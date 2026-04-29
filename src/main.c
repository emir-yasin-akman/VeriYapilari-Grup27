#include <stdio.h>
#include "graph.h"
#include "triadic.h"

int main() {

    HashTable ht = {0}; // hash table'ı sıfırla

    // kullanıcıları ekliyoruz
    insertNode(&ht, createNode(0, "User"));
    insertNode(&ht, createNode(1, "User"));
    insertNode(&ht, createNode(2, "User"));
    insertNode(&ht, createNode(3, "User"));
    insertNode(&ht, createNode(4, "User"));
    insertNode(&ht, createNode(5, "User")); // ekstra kullanıcı

    // arkadaşlık ilişkileri
    addFriendship(&ht, 0, 1);
    addFriendship(&ht, 1, 2);
    addFriendship(&ht, 0, 3);
    addFriendship(&ht, 3, 2);

    // ekstra bağlantılar,test için (senaryo genişletme)
    addFriendship(&ht, 2, 4);
    addFriendship(&ht, 4, 5);

    printf("=== TEST 1 ===\n");
    suggest_friends(&ht, 0); // kullanıcı 0 için öneri listesi

    printf("\n=== TEST 2 ===\n");
    suggest_friends(&ht, 1);

    printf("\n=== TEST 3 ===\n");
    suggest_friends(&ht, 4);

    return 0;
}