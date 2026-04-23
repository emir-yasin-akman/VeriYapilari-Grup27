#ifndef PROPERTY_H
#define PROPERTY_H

typedef struct Property {
    char key[50];
    char value[100];
    struct Property* next;
} Property;

void addProperty(Property** head, char* key, char* value);
char* getProperty(Property* head, char* key);

#endif