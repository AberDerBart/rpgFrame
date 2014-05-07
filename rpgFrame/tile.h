#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

typedef enum{
	INVALID=-1,
	NONE=0,
	SOLID=1
} collisionType;

typedef enum{
	R0=0,
	R90=1,
	R180=2,
	r270=3
} rpg_tileTextureRotation;

typedef struct{
	SDL_Texture* texture[4];
	int frames;
	int frameTime;
} rpg_tileTexture;

typedef struct{
	rpg_tileTexture** textures;
	rpg_tileTextureRotation* rot;
	collisionType collision;
	int tileId;
	int eventId;
} rpg_tile;

inline int rpg_loadTileTexture(rpg_tile*,int,int);
void rpg_freeTileTexture(rpg_tileTexture*);

#endif
