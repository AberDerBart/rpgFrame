#include "tile.h"
#include "globals.h"
#include <SDL2/SDL_image.h>

int rpg_loadTileTexture(rpg_tile* tile,int tileID,int layer){
	SDL_Surface* surface;
	char* path;
	if(tileID>=tileTypes){
		fprintf(stderr,"Unable to load texture: invalid tile ID\n");
		return -1;
	}
	if(tileID==0){
		if(layer==1){
			tile->texture_1=NULL;
		}else if(layer==2){
			tile->texture_2=NULL;
		}
		return;
	}
	
	if(tileTextures[tileID]==NULL){
		printf("loading texture #%d: %s... ",tileID,tileTextureFiles[tileID]);
		path=tileTextureFiles[tileID];

		surface=IMG_Load(path);
		if(surface==NULL){
			fprintf(stderr,"\nUnable to load texture file \"%s\": %s\n",path,IMG_GetError());
			return -1;
		}

		tileTextures[tileID]=SDL_CreateTextureFromSurface(render,surface);
		SDL_FreeSurface(surface);
		printf("done.\n");
	}
	if(layer==1){
		tile->texture_1=tileTextures[tileID];
	}else if(layer==2){
		tile->texture_2=tileTextures[tileID];
	}else{
		return -1;
	}

	return 0;
}
