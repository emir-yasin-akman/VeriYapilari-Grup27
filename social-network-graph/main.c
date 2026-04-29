// main.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "property_graph.h"

// Yardimci fonksiyonlarda diger ekip uyeleri
Node* create_node_goktug_yazcayir(int id, const char* type) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    strcpy(newNode->type, type);
    newNode->head_edge = NULL;
    return newNode;
}

void add_edge_emir_yasin_akman(Node* source, int target_id, const char* relationship) {
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    newEdge->target_id = target_id;
    strcpy(newEdge->relationship_type, relationship);
    
    newEdge->next = source->head_edge;
    source->head_edge = newEdge;
}

int main() {
    Node* graph[MAX_NODES] = {NULL};

    // Dugum ve kenar olusturma test verileri
    graph[1] = create_node_goktug_yazcayir(1, "User");   
    graph[2] = create_node_goktug_yazcayir(2, "User");   
    graph[3] = create_node_goktug_yazcayir(3, "Event");  
    graph[4] = create_node_goktug_yazcayir(4, "Photo");  

    add_edge_emir_yasin_akman(graph[1], 2, "FRIEND");     
    add_edge_emir_yasin_akman(graph[2], 3, "ATTENDS");    
    add_edge_emir_yasin_akman(graph[3], 4, "CONTAINS");   

    printf("--- Sosyal Ag Modeli Baslatildi ---\n\n");

    // Sorgu calistirma
    bfs_selim_kilicoglu(graph, 1, "FRIEND", 5);

    printf("\nIslem tamamlandi. Tum ekip uyeleri isimlendirme kuralina dahil edildi.\n");

    return 0;
}