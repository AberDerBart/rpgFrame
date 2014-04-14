#include "mainloop.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "keylist.h"
#include "character.h"

int quit;

int rpg_mainloop(){
	SDL_Event event;
	rpg_keyList* tmp_key;

	rpg_argument arg;
	arg.p=NULL;
	rpg_bindKey(SDLK_ESCAPE, &rpg_quit, arg);
	arg.i=UP;
	rpg_bindKey(SDLK_UP, &rpg_moveProtagonist, arg);
	arg.i=DOWN;
	rpg_bindKey(SDLK_DOWN, &rpg_moveProtagonist, arg);
	arg.i=LEFT;
	rpg_bindKey(SDLK_LEFT, &rpg_moveProtagonist, arg);
	arg.i=RIGHT;
	rpg_bindKey(SDLK_RIGHT, &rpg_moveProtagonist, arg);
	quit=0;
	tmp_key=&keyListStart;

	while(quit==0){
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				quit=1;		
			}
			if(event.type==SDL_KEYDOWN){
				while(tmp_key!=NULL){
					if(event.key.keysym.sym==tmp_key->key){
						tmp_key->function(tmp_key->arg);
						break;
					}
					tmp_key=tmp_key->next;
				}
				tmp_key=&keyListStart;
			}
		}
	}

	return 0;
}

void rpg_quit(void* foo){
	quit=1;
}

