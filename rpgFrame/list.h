#ifndef LIST_H
#define LIST_H

struct genericList{
	struct genericList* next;
	void* item;
	struct genericList* prev;
};

typedef struct genericList genericList;

void list_insert(genericList*, void*);

void* list_removeItem(genericList*);

genericList* list_create();

void list_forEach(genericList*,void (*)(void*));

int list_contains(genericList*, void*);

#endif
