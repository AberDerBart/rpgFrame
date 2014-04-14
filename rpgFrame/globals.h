#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#define TILE_SIZE 64

SDL_Renderer* render;

int tileTypes;
SDL_Texture** tileTextures;
char** tileTextureFiles;

#endif
