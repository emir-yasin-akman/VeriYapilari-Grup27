#include <stdlib.h>
#include <string.h>
#include "property.h"

void addProperty(Property** head, char* key, char* value) {
    Property* newProp = (Property*)malloc(sizeof(Property));
    strcpy(newProp->key, key);
    strcpy(newProp->value, value);
    newProp->next = *head;
    *head = newProp;
}

char* getProperty(Property* head, char* key) {
    while (head != NULL) {
        if (strcmp(head->key, key) == 0)
            return head->value;
        head = head->next;
    }
    return NULL;
}