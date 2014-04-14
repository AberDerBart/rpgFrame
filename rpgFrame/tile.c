#include "tile.h"
#include "globals.h"
#include <SDL2/SDL_image.h>

int rpg_loadTileTexture(rpg_tile* tile,int tileID){
	SDL_Surface* surface;
	char* path;

	if(tileID>=tileTypes){
		fprintf(stderr,"Unable to load texture: invalid tile ID\n");
		return -1;
	}
	
	if(tileTextures[tileID]==NULL){
		path=tileTextureFiles[tileID];

		surface=IMG_Load(path);
		if(surface==NULL){
			fprintf(stderr,"Unable to load texture file \"%s\": %s\n",path,IMG_GetError());
			return -1;
		}

		tileTextures[tileID]=SDL_CreateTextureFromSurface(render,surface);
		SDL_FreeSurface(surface);
	}
	tile->texture=tileTextures[tileID];

	return 0;
}
