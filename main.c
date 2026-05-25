#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash/hash.h"
#include "graph/graph.h"
#include "models/property.h"
#include "trie/trie.h"

int main() {
    HashTable ht = {0};
    TrieNode* trieRoot = createTrieNode();

    // --- KULLANICI (USER) DÜĞÜMLERİ ---
    Node* u1 = (Node*)malloc(sizeof(Node)); u1->id = 1; strcpy(u1->type, "User"); u1->edges = NULL; u1->properties = NULL;
    addProperty(&u1->properties, "name", "Ali"); insertNode(&ht, u1);

    Node* u2 = (Node*)malloc(sizeof(Node)); u2->id = 2; strcpy(u2->type, "User"); u2->edges = NULL; u2->properties = NULL;
    addProperty(&u2->properties, "name", "Veli"); insertNode(&ht, u2);

    Node* u3 = (Node*)malloc(sizeof(Node)); u3->id = 3; strcpy(u3->type, "User"); u3->edges = NULL; u3->properties = NULL;
    addProperty(&u3->properties, "name", "Ayse"); insertNode(&ht, u3);

    Node* u4 = (Node*)malloc(sizeof(Node)); u4->id = 4; strcpy(u4->type, "User"); u4->edges = NULL; u4->properties = NULL;
    addProperty(&u4->properties, "name", "Fatma"); insertNode(&ht, u4);

    Node* u5 = (Node*)malloc(sizeof(Node)); u5->id = 5; strcpy(u5->type, "User"); u5->edges = NULL; u5->properties = NULL;
    addProperty(&u5->properties, "name", "Mehmet"); insertNode(&ht, u5);

    // --- ETKINLIK (EVENT) DÜĞÜMLERİ ---
    Node* e1 = (Node*)malloc(sizeof(Node)); e1->id = 11; strcpy(e1->type, "Event"); e1->edges = NULL; e1->properties = NULL;
    addProperty(&e1->properties, "name", "Bilgisayar Muhendisligi Hackathonu"); insertNode(&ht, e1);

    Node* e2 = (Node*)malloc(sizeof(Node)); e2->id = 12; strcpy(e2->type, "Event"); e2->edges = NULL; e2->properties = NULL;
    addProperty(&e2->properties, "name", "Tiyatro Festivali"); insertNode(&ht, e2);

    // --- FOTOĞRAF (PHOTO) DÜĞÜMLERİ ---
    Node* p1 = (Node*)malloc(sizeof(Node)); p1->id = 15; strcpy(p1->type, "Photo"); p1->edges = NULL; p1->properties = NULL;
    addProperty(&p1->properties, "name", "hackathon_hatirasi.jpg"); insertNode(&ht, p1);

    Node* p2 = (Node*)malloc(sizeof(Node)); p2->id = 16; strcpy(p2->type, "Photo"); p2->edges = NULL; p2->properties = NULL;
    addProperty(&p2->properties, "name", "sahne_arkasi.png"); insertNode(&ht, p2);

    // --- İLİŞKİLERİN BAĞLANMASI (addEdge güncellendi: FRIEND yönsüz yapıldı) ---
    addEdge(&ht, 1, 2, "FRIEND", 0); // Ali <-> Veli (Yönsüz)
    addEdge(&ht, 1, 3, "FRIEND", 0); // Ali <-> Ayse
    addEdge(&ht, 3, 4, "FRIEND", 0); // Ayse <-> Fatma
    addEdge(&ht, 1, 5, "FRIEND", 0); // Ali <-> Mehmet

    addEdge(&ht, 2, 11, "ATTENDS", 1); // Veli -> Hackathon (Yönlü)
    addEdge(&ht, 5, 11, "ATTENDS", 1); // Mehmet -> Hackathon

    addEdge(&ht, 11, 15, "HAS_PHOTO", 1); // Hackathon -> Fotoğraf

    // --- TRIE INDEKSLENMESI VE METIN ARAMA TESTI ---
    indexGraphWithTrie(&ht, trieRoot);
    searchAndPrintNodesByPrefix(&ht, trieRoot, "Al"); // "Ali"yi bulacak
    searchAndPrintNodesByPrefix(&ht, trieRoot, "Ve"); // "Veli"yi bulacak

    // --- DIGER STANDART TESTLER ---
    printf("\n--- FILTERED BFS TEST ---\n");
    filteredBFS(&ht, 1, "ATTENDS");

    printf("\n--- BFS SORGUSU ---\n");
    BFS(&ht, 1);

    printf("\n--- MULTI-STEP QUERY (Faz 2 İsteri) ---\n");
    findPhotosOfFriendsEvents(&ht, 1);

    printNodeCentrality(&ht);

    // --- FAZ 3: GÖRSELLEŞTİRME ÇIKTISI ÜRETME ---
    exportGraphToDOT(&ht, "sosyal_ag_grafigi.dot");

    // --- TEMİZLİK ---
    printf("\nProgram sonlaniyor, bellek temizleniyor...\n");
    freeGraph(&ht);
    // Not: TrieNode temizleme fonksiyonu eklenebilir, basitlik adına program sonlanırken OS temizleyecektir.

    return 0;
}
