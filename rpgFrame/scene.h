#ifndef SCENE_H
#define SCENE_H

#include "map.h"
#include "character.h"
#include "list.h"

typedef struct{
	rpg_map* map;
	genericList* chars;
	rpg_character* focus;
	int off_x;
	int off_y;
} rpg_scene;

void rpg_drawScene(rpg_scene*);

void rpg_setFocus(rpg_scene*,rpg_character*);

#endif
