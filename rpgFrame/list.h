#ifndef LIST_H
#define LIST_H

#include "structs.h"

void list_insert(genericList*, void*);

void* list_removeItem(genericList*);

genericList* list_create();

void list_forEach(genericList*,void (*)(void*));

genericList* list_contains(genericList*, void*);

#endif
