#ifndef KEYLIST_H
#define KEYLIST_H

#include <SDL2/SDL.h>

typedef union{
	void* p;
	int i;
} rpg_argument;

struct rpg_keyList{
	SDL_Keycode key;
	void (*function)(rpg_argument);
	rpg_argument arg;
	struct rpg_keyList* next;
};

typedef struct rpg_keyList rpg_keyList;

rpg_keyList keyListStart;

void rpg_bindKey(SDL_Keycode, void (*)(),rpg_argument);

void rpg_freeKeys();

#endif
