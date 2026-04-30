// property_graph.h
#ifndef PROPERTY_GRAPH_H
#define PROPERTY_GRAPH_H

#include <stdbool.h>

#define MAX_NODES 1000 

typedef struct Edge {
    int target_id;
    char relationship_type[20]; 
    struct Edge* next;
} Edge;

typedef struct Node {
    int id;               
    char type[20];        
    Edge* head_edge;      
} Node;

// Ekip uyelerinin isimleriyle fonksiyon prototipleri
void enqueue_murat_pangal(int node_id);
int dequeue_gizem_yurtseven();
bool is_empty_murat_yilmaz_carikci();

// Ana BFS algoritmasi
void bfs_selim_kilicoglu(Node* graph_nodes[], int start_id, const char* target_relationship, int total_nodes);

#endif