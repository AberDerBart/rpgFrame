#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>

#include "structs.h"

inline int rpg_loadTileTexture(rpg_tile*,int,int);
void rpg_freeTileTexture(rpg_tileTexture*);

#endif
