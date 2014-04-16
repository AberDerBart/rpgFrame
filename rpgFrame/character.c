#include "character.h"
#include <SDL2/SDL_image.h>
#include "globals.h"
#include <stdio.h>
#include "mainloop.h"
#include "list.h"

rpg_character* rpg_createCharacter(char* texPath){
	rpg_character* character;
	SDL_Surface* surface;

	surface=IMG_Load(texPath);
	if(surface==NULL){
		fprintf(stderr,"Unable to load texture file \"%s\": %s\n",texPath,IMG_GetError());
		return NULL;
	}

	character=malloc(sizeof(rpg_character));

	character->texture=SDL_CreateTextureFromSurface(render,surface);
	SDL_FreeSurface(surface);

	character->x=0;
	character->y=0;
	character->step_x=0;
	character->step_y=0;
	character->state=NORMAL;

	return character;
}

void rpg_drawCharacter(rpg_character* character){
	SDL_Rect rect;
	rect.w=TILE_SIZE;
	rect.h=TILE_SIZE;
	rect.x=character->x*TILE_SIZE+character->step_x-rpg_curScene->off_x;
	rect.y=character->y*TILE_SIZE+character->step_y-rpg_curScene->off_y;
	SDL_RenderCopy(render,character->texture,NULL,&rect);
}
	
int rpg_moveCharacter(rpg_character* character, rpg_direction direction){
	if(checkCollision(character,direction)!=NORMAL){
		return 3;
	}
	movedObject* mObject;
	genericList* list;

	if(character->state==MOVING){
		while(list->item!=character){
			if(list->next==NULL){
				return 2;
			}
			list=list->next;
		}
		return 1;
	}

	mObject=malloc(sizeof(movedObject));

	mObject->c=character;
	mObject->dir=direction;
	mObject->speed=2.;
	mObject->startTime=SDL_GetTicks();

	list_insert(movedObjectsList,mObject);
	character->state=MOVING;

	return 0;
}

void rpg_moveProtagonist(rpg_direction direction){
	if(rpg_protagonist){
		rpg_moveCharacter(rpg_protagonist, direction);
	}
}

rpg_direction nextPlayerDir;

void startMovement(rpg_direction dir){
	nextPlayerDir=dir;
}

void stopMovement(rpg_direction dir){
	if(dir==nextPlayerDir){
		nextPlayerDir=D_NONE;
	}
}

void updatePlayerMovement(){
	if(rpg_protagonist){
		if(nextPlayerDir!=NONE){
			if(rpg_protagonist->state!=MOVING){
				rpg_moveProtagonist(nextPlayerDir);
			}
		}
	}
}

collisionType checkCollision(rpg_character* chara,rpg_direction dir){
	rpg_tile* tile;

	tile=rpg_getMapTile(rpg_curScene->map,chara->x,chara->y,dir);

	if(tile){
		return tile->collision;
	}
	return -1;
}
