#ifndef MAP_H
#define MAP_H

#include "tile.h"
#include "character.h"
#include "list.h"

typedef struct{
	int height;
	int width;
	int layers;
	rpg_tile* tiles;
	genericList* chars;
} rpg_map; 

inline rpg_map* rpg_createMap(int,int,int);

inline int rpg_drawMap(rpg_map*);

rpg_tile* rpg_getMapTile(rpg_map*,int,int,rpg_direction);

#endif
