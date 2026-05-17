#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash/hash.h"
#include "graph/graph.h"
#include "models/property.h"

int main() {
    HashTable ht = {0};

    // Node 1
    Node* n1 = (Node*)malloc(sizeof(Node));
    n1->id = 1;
    strcpy(n1->type, "User");
    n1->edges = NULL;
    n1->properties = NULL;

    addProperty(&n1->properties, "name", "Ali");

    // Node 2
    Node* n2 = (Node*)malloc(sizeof(Node));
    n2->id = 2;
    strcpy(n2->type, "User");
    n2->edges = NULL;
    n2->properties = NULL;

    addProperty(&n2->properties, "name", "Veli");

    // Node 3
    Node* n3 = (Node*)malloc(sizeof(Node));
    n3->id = 3;
    strcpy(n3->type, "User");
    n3->edges = NULL;
    n3->properties = NULL;

    addProperty(&n3->properties, "name", "Ayse");

    insertNode(&ht, n1);
    insertNode(&ht, n2);
    insertNode(&ht, n3);

    // Node 4 - Event (Etkinlik) olusturuyoruz
    Node* n4 = (Node*)malloc(sizeof(Node));
    n4->id = 4;
    strcpy(n4->type, "Event");
    n4->edges = NULL;
    n4->properties = NULL;
    addProperty(&n4->properties, "name", "Bilgisayar Muhendisligi Hackathonu");
    insertNode(&ht, n4);

    // Node 5 - Photo (Fotograf) olusturuyoruz
    Node* n5 = (Node*)malloc(sizeof(Node));
    n5->id = 5;
    strcpy(n5->type, "Photo");
    n5->edges = NULL;
    n5->properties = NULL;
    addProperty(&n5->properties, "name", "hackathon_hatirasi.jpg");
    insertNode(&ht, n5);

    // Karşılıklı arkadaşlık (undirected friendship) ilişkileri
    addEdge(&ht, 1, 2, "FRIEND");
    addEdge(&ht, 2, 1, "FRIEND");
    addEdge(&ht, 1, 3, "FRIEND");
    addEdge(&ht, 3, 1, "FRIEND");

    // Ali'yi etkinlige bagla
    addEdge(&ht, 1, 4, "ATTENDS");

    // Veli'yi (Node 2) Hackathon'a (Node 4) bağla
    addEdge(&ht, 2, 4, "ATTENDS");

    // Hackathon'u (Node 4) Fotograf düğümüne (Node 5) bağla
    addEdge(&ht, 4, 5, "HAS_PHOTO");


    // Yeni yazdigimiz filtreli aramayi test et
    printf("\n--- FILTERED BFS TEST ---\n");
    printf("Ali'nin (Node 1) sadece katildigi etkinlikler ('ATTENDS' filtresi):\n");
    filteredBFS(&ht, 1, "ATTENDS");

    printf("BFS:\n");
    BFS(&ht, 1);

    printf("\nDFS:\n");
    DFS(&ht, 1);

    printf("\nTriadic closure recommendations:\n");
    recommendFriends(&ht, 2, 1);
    recommendFriends(&ht, 3, 1);

    printNodeCentrality(&ht);

    // Faz 2: Multi-step query traversal - Ali'nin arkadaşlarının katıldığı etkinliklerdeki fotoğraflar
    findPhotosOfFriendsEvents(&ht, 1);
    
    printf("Program terminating, memory is being cleaned...\n");
    freeGraph(&ht);

    return 0;
}