#include "list.h"
#include <stdlib.h>

void list_insert(genericList* list, void* item){
	genericList *prev,*next,*listItem;

	prev=list;
	next=list->next;
	listItem=list_create();
	listItem->next=next;
	listItem->prev=prev;
	prev->next=listItem;
	if(next){
		next->prev=listItem;
	}
	listItem->item=item;
}

void* list_removeItem(genericList* list){
	genericList *prev,*next;
	void* item;
	item=list->item;
	prev=list->prev;
	next=list->next;
	if(prev){
		prev->next=next;
	}
	if(next){
		next->prev=prev;
	}
	free(list);
	return item;
}

genericList* list_create(){
	genericList* list;
	list=malloc(sizeof(genericList));
	list->next=NULL;
	list->item=NULL;
	list->prev=NULL;
	return list;
}

void list_forEach(genericList* list,void (*func)(void*)){
	list=list->next;
	while(list){
		func(list->item);
		list=list->next;
	}
}
	
