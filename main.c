#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash/hash.h"
#include "graph/graph.h"
#include "models/property.h"

int main() {
    HashTable ht = {0};

    // --- 10 UNIQUE KULLANICI (USER) DUGUMU ---
    Node* u1 = (Node*)malloc(sizeof(Node));
    u1->id = 1;
    strcpy(u1->type, "User");
    u1->edges = NULL;
    u1->properties = NULL;
    addProperty(&u1->properties, "name", "Ali");
    insertNode(&ht, u1);

    Node* u2 = (Node*)malloc(sizeof(Node));
    u2->id = 2;
    strcpy(u2->type, "User");
    u2->edges = NULL;
    u2->properties = NULL;
    addProperty(&u2->properties, "name", "Veli");
    insertNode(&ht, u2);

    Node* u3 = (Node*)malloc(sizeof(Node));
    u3->id = 3;
    strcpy(u3->type, "User");
    u3->edges = NULL;
    u3->properties = NULL;
    addProperty(&u3->properties, "name", "Ayse");
    insertNode(&ht, u3);

    Node* u4 = (Node*)malloc(sizeof(Node));
    u4->id = 4;
    strcpy(u4->type, "User");
    u4->edges = NULL;
    u4->properties = NULL;
    addProperty(&u4->properties, "name", "Fatma");
    insertNode(&ht, u4);

    Node* u5 = (Node*)malloc(sizeof(Node));
    u5->id = 5;
    strcpy(u5->type, "User");
    u5->edges = NULL;
    u5->properties = NULL;
    addProperty(&u5->properties, "name", "Mehmet");
    insertNode(&ht, u5);

    Node* u6 = (Node*)malloc(sizeof(Node));
    u6->id = 6;
    strcpy(u6->type, "User");
    u6->edges = NULL;
    u6->properties = NULL;
    addProperty(&u6->properties, "name", "Zeynep");
    insertNode(&ht, u6);

    Node* u7 = (Node*)malloc(sizeof(Node));
    u7->id = 7;
    strcpy(u7->type, "User");
    u7->edges = NULL;
    u7->properties = NULL;
    addProperty(&u7->properties, "name", "Burak");
    insertNode(&ht, u7);

    Node* u8 = (Node*)malloc(sizeof(Node));
    u8->id = 8;
    strcpy(u8->type, "User");
    u8->edges = NULL;
    u8->properties = NULL;
    addProperty(&u8->properties, "name", "Ebru");
    insertNode(&ht, u8);

    Node* u9 = (Node*)malloc(sizeof(Node));
    u9->id = 9;
    strcpy(u9->type, "User");
    u9->edges = NULL;
    u9->properties = NULL;
    addProperty(&u9->properties, "name", "Cem");
    insertNode(&ht, u9);

    Node* u10 = (Node*)malloc(sizeof(Node));
    u10->id = 10;
    strcpy(u10->type, "User");
    u10->edges = NULL;
    u10->properties = NULL;
    addProperty(&u10->properties, "name", "Gamze");
    insertNode(&ht, u10);

    // --- 4 ETKINLIK (EVENT) DUGUMU ---
    Node* e1 = (Node*)malloc(sizeof(Node));
    e1->id = 11;
    strcpy(e1->type, "Event");
    e1->edges = NULL;
    e1->properties = NULL;
    addProperty(&e1->properties, "name", "Bilgisayar Muhendisligi Hackathonu");
    insertNode(&ht, e1);

    Node* e2 = (Node*)malloc(sizeof(Node));
    e2->id = 12;
    strcpy(e2->type, "Event");
    e2->edges = NULL;
    e2->properties = NULL;
    addProperty(&e2->properties, "name", "Tiyatro Festivali");
    insertNode(&ht, e2);

    Node* e3 = (Node*)malloc(sizeof(Node));
    e3->id = 13;
    strcpy(e3->type, "Event");
    e3->edges = NULL;
    e3->properties = NULL;
    addProperty(&e3->properties, "name", "Girisimcilik Zirvesi");
    insertNode(&ht, e3);

    Node* e4 = (Node*)malloc(sizeof(Node));
    e4->id = 14;
    strcpy(e4->type, "Event");
    e4->edges = NULL;
    e4->properties = NULL;
    addProperty(&e4->properties, "name", "Kampus Konseri");
    insertNode(&ht, e4);

    // --- 5 FOTOGRAF (PHOTO) DUGUMU ---
    Node* p1 = (Node*)malloc(sizeof(Node));
    p1->id = 15;
    strcpy(p1->type, "Photo");
    p1->edges = NULL;
    p1->properties = NULL;
    addProperty(&p1->properties, "name", "hackathon_hatirasi.jpg");
    insertNode(&ht, p1);

    Node* p2 = (Node*)malloc(sizeof(Node));
    p2->id = 16;
    strcpy(p2->type, "Photo");
    p2->edges = NULL;
    p2->properties = NULL;
    addProperty(&p2->properties, "name", "sahne_arkasi.png");
    insertNode(&ht, p2);

    Node* p3 = (Node*)malloc(sizeof(Node));
    p3->id = 17;
    strcpy(p3->type, "Photo");
    p3->edges = NULL;
    p3->properties = NULL;
    addProperty(&p3->properties, "name", "proje_sunumu.jpg");
    insertNode(&ht, p3);

    Node* p4 = (Node*)malloc(sizeof(Node));
    p4->id = 18;
    strcpy(p4->type, "Photo");
    p4->edges = NULL;
    p4->properties = NULL;
    addProperty(&p4->properties, "name", "konser_alani.jpg");
    insertNode(&ht, p4);

    Node* p5 = (Node*)malloc(sizeof(Node));
    p5->id = 19;
    strcpy(p5->type, "Photo");
    p5->edges = NULL;
    p5->properties = NULL;
    addProperty(&p5->properties, "name", "grup_selfie.png");
    insertNode(&ht, p5);

    // --- STATIK ILISKILERIN (EDGES) BAGLANMASI ---
    // Arkadaşlıklar (FRIEND)
    addEdge(&ht, 1, 2, "FRIEND");
    addEdge(&ht, 2, 1, "FRIEND");
    addEdge(&ht, 1, 3, "FRIEND");
    addEdge(&ht, 3, 1, "FRIEND");
    addEdge(&ht, 3, 4, "FRIEND");
    addEdge(&ht, 5, 6, "FRIEND");
    addEdge(&ht, 7, 8, "FRIEND");
    addEdge(&ht, 9, 10, "FRIEND");
    addEdge(&ht, 1, 5, "FRIEND");

    // Etkinlik Katilimları (ATTENDS)
    addEdge(&ht, 2, 11, "ATTENDS");
    addEdge(&ht, 5, 11, "ATTENDS");
    addEdge(&ht, 4, 12, "ATTENDS");
    addEdge(&ht, 6, 12, "ATTENDS");
    addEdge(&ht, 7, 13, "ATTENDS");
    addEdge(&ht, 8, 13, "ATTENDS");
    addEdge(&ht, 1, 14, "ATTENDS");
    addEdge(&ht, 10, 14, "ATTENDS");

    // Etkinlik - Fotograf Baglari (HAS_PHOTO)
    addEdge(&ht, 11, 15, "HAS_PHOTO");
    addEdge(&ht, 11, 17, "HAS_PHOTO");
    addEdge(&ht, 12, 16, "HAS_PHOTO");
    addEdge(&ht, 14, 18, "HAS_PHOTO");
    addEdge(&ht, 14, 19, "HAS_PHOTO");

    // --- TEMEL ANALIZLER VE TEST ÇAĞRILARI ---
    printf("\n--- FILTERED BFS TEST ---\n");
    printf("Ali'nin (Node 1) sadece katildigi etkinlikler ('ATTENDS' filtresi):\n");
    filteredBFS(&ht, 1, "ATTENDS");

    printf("\nBFS:\n");
    BFS(&ht, 1);

    printf("\nDFS:\n");
    DFS(&ht, 1);

    printf("\nTriadic closure recommendations:\n");
    recommendFriends(&ht, 2, 1);
    recommendFriends(&ht, 3, 1);

    printNodeCentrality(&ht);

    // Faz 2: Multi-step query traversal - Ali'nin arkadaşlarının katıldığı etkinliklerdeki fotoğraflar
    findPhotosOfFriendsEvents(&ht, 1);
    
    // --- SENTETIK VERI INJEKSIYONU VE DINAMIK GORSELLESTIRILME ---
    generateSyntheticData(&ht, 50, 10, 15, 120);
    
    printf("Program terminating, memory is being cleaned...\n");
    freeGraph(&ht);

    return 0;
}