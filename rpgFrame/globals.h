#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#define TILE_SIZE 64
#include "gui.h"
#include "tile.h"

SDL_Renderer* render;

rpg_guiStyle* guiStyle;

int tileTypes;
rpg_tileTexture** tileTextures;
char** tileTextureFiles;

#endif
