#include "tile.h"
#include "globals.h"
#include <SDL2/SDL_image.h>

int rpg_loadTileTexture(rpg_tile* tile,int tileID,int layer){
	SDL_Surface* surface;
	char* path;
	if(tileID>tileTypes){
		fprintf(stderr,"Unable to load texture: invalid tile ID\n");
		return -1;
	}
	if(tileID==0){
		tile->textures[layer]=NULL;
		return;
	}
	
	if(tileTextures[tileID]->texture==NULL){
		printf("loading texture #%d: %s... ",tileID,tileTextureFiles[tileID]);
		path=tileTextureFiles[tileID];

		surface=IMG_Load(path);
		if(surface==NULL){
			fprintf(stderr,"\nUnable to load texture file \"%s\": %s\n",path,IMG_GetError());
			return -1;
		}

		tileTextures[tileID]->texture=SDL_CreateTextureFromSurface(render,surface);
		SDL_FreeSurface(surface);
		printf("done.\n");
	}

	tile->textures[layer]=tileTextures[tileID];
	return 0;
}

void rpg_freeTileTexture(rpg_tileTexture* tex){
	if(tex->texture){
		SDL_DestroyTexture(tex->texture);
	}
	//free(tex);
}
