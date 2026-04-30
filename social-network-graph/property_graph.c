// property_graph.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "property_graph.h"

int queue[MAX_NODES];
int front = -1, rear = -1;

void enqueue_murat_pangal(int node_id) {
    if (rear == MAX_NODES - 1) return;
    if (front == -1) front = 0;
    queue[++rear] = node_id;
}

int dequeue_gizem_yurtseven() {
    if (front == -1 || front > rear) return -1;
    return queue[front++];
}

bool is_empty_murat_yilmaz_carikci() {
    return (front == -1 || front > rear);
}

void bfs_selim_kilicoglu(Node* graph_nodes[], int start_id, const char* target_relationship, int total_nodes) {
    bool visited[MAX_NODES] = {false};
    
    front = -1; rear = -1;
    enqueue_murat_pangal(start_id);
    visited[start_id] = true;
    
    printf("Sorgu Sonuclari (%s iliskisi):\n", target_relationship);
    
    while (!is_empty_murat_yilmaz_carikci()) {
        int current_id = dequeue_gizem_yurtseven();
        Node* current_node = graph_nodes[current_id]; 
        
        if (current_id != start_id) {
            printf("- Bulunan Dugum ID: %d (Tur: %s)\n", current_node->id, current_node->type);
        }
        
        Edge* temp_edge = current_node->head_edge;
        while (temp_edge != NULL) {
            if (strcmp(temp_edge->relationship_type, target_relationship) == 0) {
                int adj_id = temp_edge->target_id;
                
                if (!visited[adj_id]) {
                    visited[adj_id] = true;
                    enqueue_murat_pangal(adj_id);
                }
            }
            temp_edge = temp_edge->next;
        }
    }
}