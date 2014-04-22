#ifndef GLOBALS_H
#define GLOBALS_H

#include <SDL2/SDL.h>
#define TILE_SIZE 64
#include "gui.h"

SDL_Renderer* render;

rpg_guiStyle* gui;
rpg_guiTextStyle* tGui;

int tileTypes;
SDL_Texture** tileTextures;
char** tileTextureFiles;

#endif
