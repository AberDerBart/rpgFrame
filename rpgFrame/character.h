#ifndef CHARAKTER_H
#define CHARAKTER_H

#include <SDL2/SDL.h>
#include "tile.h"

typedef enum{
	D_NONE=0,
	D_UP=1,
	D_LEFT=2,
	D_DOWN=3,
	D_RIGHT=4
} rpg_direction;

typedef enum{
	NORMAL,
	MOVING
} rpg_characterState;

typedef struct{
	int x;
	int y;
	int step_x;
	int step_y;
	int sprite_frames;
	SDL_Texture* texture;
	rpg_characterState state;
	rpg_direction dir;
} rpg_character;

rpg_character* rpg_protagonist;

rpg_character* rpg_createCharacter(char*);

void rpg_setProtagonst(rpg_character*);

void rpg_drawCharacter(rpg_character*);

int rpg_moveCharacter(rpg_character*, rpg_direction);

void rpg_moveProtagonist(rpg_direction);

void startMovement(rpg_direction);
void stopMovement(rpg_direction);
void updatePlayerMovement();
collisionType checkCollision(rpg_character*,rpg_direction);

#endif
