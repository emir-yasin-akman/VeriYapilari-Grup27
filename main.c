#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash/hash.h"
#include "graph/graph.h"
#include "queue/queue.h"

int main() {
    HashTable ht = {0};

    Node* n1 = (Node*)malloc(sizeof(Node));
    n1->id = 1;
    strcpy(n1->type, "User");
    n1->edges = NULL;

    Node* n2 = (Node*)malloc(sizeof(Node));
    n2->id = 2;
    strcpy(n2->type, "User");
    n2->edges = NULL;

    insertNode(&ht, n1);
    insertNode(&ht, n2);

    addEdge(&ht, 1, 2, "FRIEND");

    printf("Graph hazır.\n");

    return 0;
}