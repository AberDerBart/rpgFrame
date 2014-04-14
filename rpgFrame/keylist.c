#include "keylist.h"

void rpg_bindKey(SDL_Keycode key, void (*function)(),argument arg){
	rpg_keyList* list;

	list=&keyListStart;

	while(list->next!=NULL){
		list=list->next;
	}
	
	list->key=key;
	list->function=function;
	list->arg=arg;
	list->next=malloc(sizeof(rpg_keyList));

	list->next->next=NULL;
}

void freeKey(rpg_keyList* keyItem){
	if(keyItem->next!=NULL){
		freeKey(keyItem->next);
	}
	free(keyItem);
}

void rpg_freeKeys(){
	freeKey(keyListStart.next);
	keyListStart.function=NULL;
	keyListStart.key=0;
	keyListStart.next=NULL;
}
