#ifndef KEYLIST_H
#define KEYLIST_H

#include <SDL2/SDL.h>

typedef union{
	void* v;
	int i;
} argument;

struct rpg_keyList{
	SDL_Keycode key;
	void (*function)(void*);
	argument arg;
	struct rpg_keyList* next;
};

typedef struct rpg_keyList rpg_keyList;

rpg_keyList keyListStart;

void rpg_bindKey(SDL_Keycode, void (*)(),argument);

void rpg_freeKeys();

#endif
