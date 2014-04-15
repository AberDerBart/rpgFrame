#include "mainloop.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "keylist.h"
#include "character.h"
#include "globals.h"

int quit;

void moveObjects();

int rpg_mainloop(){
	SDL_Event event;
	rpg_keyList* tmp_key;
	Uint32 time0;
	int frameTime;

	movedObjectsList=list_create();

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

	time0=SDL_GetTicks();

	while(quit==0){
		frameTime=SDL_GetTicks()-time0;
		time0=SDL_GetTicks();

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
		moveObjects();
		redraw();
	}

	return 0;
}

int moveObject(int time, movedObject* obj){
	int step;

	step=(time-obj->startTime)*TILE_SIZE*obj->speed/1000.;

	if(obj->dir==RIGHT){
		if(step<TILE_SIZE){
			obj->c->step_x=step;
		}else{
			obj->c->step_x=0;
			obj->c->x++;
		}
	}

	if(obj->dir==LEFT){
		if(step<TILE_SIZE){
			obj->c->step_x=-step;
		}else{
			obj->c->step_x=0;
			obj->c->x--;
		}
	}

	if(obj->dir==UP){
		if(step<TILE_SIZE){
			obj->c->step_y=-step;
		}else{
			obj->c->step_y=0;
			obj->c->y--;
		}
	}

	if(obj->dir==DOWN){
		if(step<TILE_SIZE){
			obj->c->step_y=step;
		}else{
			obj->c->step_y=0;
			obj->c->y++;
		}
	}

	if(step<TILE_SIZE){
		return 0;
	}else{
		obj->c->state=NORMAL;
		return 1;
	}
}

void moveObjects(){
	Uint32 time;
	genericList* list;
	genericList* tmp;

	time=SDL_GetTicks();
	list=movedObjectsList->next;

	while(list){
		if(moveObject(time,list->item)){
			tmp=list;
			list=list->next;
			list_removeItem(tmp);
		}else{
			list=list->next;
		}
	}
}

void rpg_quit(void* foo){
	quit=1;
}

void rpg_redraw(){
	
}

