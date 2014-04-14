#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

typedef enum{
	NONE=0,
	SOLID=1
} collisionType;

typedef struct{
	SDL_Texture* texture;
	collisionType collision;
	int tileId;
} rpg_tile;

inline int rpg_loadTileTexture(rpg_tile*,int);

#endif
