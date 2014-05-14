#ifndef CHARAKTER_H
#define CHARAKTER_H

#include <SDL2/SDL.h>
#include "tile.h"
#include "map.h"
#include "structs.h"

rpg_character* rpg_protagonist;

rpg_character* rpg_createCharacter(char*);

void rpg_setProtagonist(rpg_character*);

void rpg_drawCharacter(rpg_character*);

int rpg_moveCharacter(rpg_character*, rpg_direction);

void rpg_moveProtagonist(rpg_direction);

void startMovement(rpg_direction);
void stopMovement(rpg_direction);
void updatePlayerMovement();
collisionType checkCollision(rpg_character*,rpg_direction);

#endif
