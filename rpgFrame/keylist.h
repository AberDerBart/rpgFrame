#ifndef KEYLIST_H
#define KEYLIST_H

#include <SDL2/SDL.h>

typedef union{
	void* p;
	int i;
} rpg_argument;

struct rpg_keyList{
	SDL_Keycode key;
	void (*function)();
	//rpg_argument arg;
	struct rpg_keyList* next;
};

SDL_Keycode movementKeys[4];

typedef struct rpg_keyList rpg_keyList;

rpg_keyList keyListStart;

void rpg_bindKey(SDL_Keycode, void (*)());

void rpg_freeKeys();

#endif
