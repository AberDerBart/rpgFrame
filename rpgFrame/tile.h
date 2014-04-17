#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

typedef enum{
	INVALID=-1,
	NONE=0,
	SOLID=1
} collisionType;

typedef struct{
	SDL_Texture** textures;
	collisionType collision;
	int tileId;
} rpg_tile;

inline int rpg_loadTileTexture(rpg_tile*,int,int);

#endif
