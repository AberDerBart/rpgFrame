#ifndef MAP_H
#define MAP_H

#include "tile.h"

typedef struct{
	int height;
	int width;
	rpg_tile* tiles;
} rpg_map; 

inline rpg_map* rpg_createMap(int,int);

inline int rpg_drawMap(rpg_map*);

#endif
