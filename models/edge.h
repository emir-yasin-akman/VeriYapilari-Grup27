#ifndef EDGE_H
#define EDGE_H

typedef struct Edge {
    int target_id;
    char relation[20];
    char date[20];
    struct Edge* next;
} Edge;

#endif