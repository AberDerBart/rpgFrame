#include "character.h"
#include <SDL2/SDL_image.h>
#include "globals.h"
#include <stdio.h>

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

	return character;
}

void rpg_drawCharacter(rpg_character* character){
	SDL_Rect rect;
	rect.w=TILE_SIZE;
	rect.h=TILE_SIZE;
	rect.x=character->x*TILE_SIZE+character->step_x;
	rect.y=character->x*TILE_SIZE+character->step_y;
	SDL_RenderCopy(render,character->texture,NULL,&rect);
	SDL_RenderPresent(render);
}
	
void rpg_moveCharacter(rpg_character* character, rpg_direction direction){
	
}

void rpg_moveProtagonist(rpg_direction direction){
	if(rpg_protagonist){
		rpg_moveCharacter(rpg_protagonist, direction);
	}
}
