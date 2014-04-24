#include "mainloop.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "keylist.h"
#include "character.h"
#include "globals.h"
#include "events.h"

int quit;

void moveObjects();

int rpg_mainloop(){
	SDL_Event event;
	rpg_keyList* tmp_key;
	int i;


	movedObjectsList=list_create();

	//rpg_bindKey(SDLK_ESCAPE, &rpg_quit, NULL);

	movementKeys[0]=SDLK_UP;
	movementKeys[1]=SDLK_LEFT;
	movementKeys[2]=SDLK_DOWN;
	movementKeys[3]=SDLK_RIGHT;

	rpg_bindKey(SDLK_ESCAPE,&rpg_quit);

	quit=0;

	while(quit==0){
		while(SDL_PollEvent(&event)){
			if(event.type==SDL_QUIT){
				quit=1;		
			}
			if(event.type==SDL_KEYDOWN){
				tmp_key=&keyListStart;
				for(i=1;i<5;i++){ 
					if(event.key.keysym.sym==movementKeys[i-1]){
						startMovement(i);
					}
				}
				while(tmp_key!=NULL){
					if(event.key.keysym.sym==tmp_key->key){
						tmp_key->function();
						break;
					}
					tmp_key=tmp_key->next;
				}
			}
			if(event.type==SDL_KEYUP){
				for(i=1;i<5;i++){ 
					if(event.key.keysym.sym==movementKeys[i-1]){
						stopMovement(i);
					}
				}
			}
		}
		updatePlayerMovement();
		moveObjects();
		rpg_redraw();
	}

	return 0;
}

int moveObject(int time, movedObject* obj){
	int step;

	step=(time-obj->startTime)*TILE_SIZE*obj->speed/1000.;

	if(obj->dir==D_RIGHT){
		if(step<TILE_SIZE){
			obj->c->step_x=step;
		}else{
			obj->c->step_x=0;
			obj->c->x++;
		}
	}
	if(obj->dir==D_LEFT){
		if(step<TILE_SIZE){
			obj->c->step_x=-step;
		}else{
			obj->c->step_x=0;
			obj->c->x--;
		}
	}
	if(obj->dir==D_UP){
		if(step<TILE_SIZE){
			obj->c->step_y=-step;
		}else{
			obj->c->step_y=0;
			obj->c->y--;
		}
	}
	if(obj->dir==D_DOWN){
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
		if(obj->nextDir==D_NONE){
			obj->c->state=NORMAL;
			return 1;
		}else{
			obj->startTime=time;
			obj->dir=obj->nextDir;
			return 0;
		}
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
			//((movedObject*)tmp->item)->c->state=NORMAL;
			list=list->next;
			if(((movedObject*) tmp->item)->c==rpg_protagonist){
				rpg_checkEvent_stand();
			}
			list_removeItem(tmp);
		}else{
			list=list->next;
		}
	}
}

void rpg_quit(){
	quit=1;
}

void rpg_redraw(){
	SDL_RenderClear(render);
	if(rpg_curScene){
		rpg_drawScene(rpg_curScene);
	}		
	rpg_drawGui();
	SDL_RenderPresent(render);
}

