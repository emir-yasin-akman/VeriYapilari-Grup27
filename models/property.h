#ifndef PROPERTY_H
#define PROPERTY_H

typedef struct Property {
    char key[50];
    char value[100];
    struct Property* next;
} Property;

#endif