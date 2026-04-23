#ifndef NODE_H
#define NODE_H

#include "edge.h"
#include "property.h"

typedef struct Node {
    int id;
    char type[20];
    Property* properties;
    Edge* edges;
} Node;

#endif