#include "mapParser.h"
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string.h>

#include "globals.h"
#include "tile.h"

int rpg_setTiletable(char* tileTablePath){
	FILE* tableFile;
	int i,lines;
	char buffer[512];

	//read tile Table
	tableFile=fopen(tileTablePath,"r");
	if(!tableFile){
		fprintf(stderr,"could not read tile table\n");
		return -1;
	}
	lines=0;
	while(fgets(buffer,512,tableFile)){
		lines++;
	}
	rewind(tableFile);
	tileTextureFiles=malloc((lines+1)*sizeof(char*));
	tileTextures=malloc((lines+1)*sizeof(SDL_Texture*));
	tileTypes=lines;
	tileTextureFiles[0]=NULL;
	tileTextures[0]=NULL;
	for(i=1;i<=lines;i++){
		fgets(buffer,512,tableFile);
		buffer[strlen(buffer)-1]=0;
		tileTextureFiles[i]=malloc((strlen(buffer)+1)*sizeof(char*));
		strcpy(tileTextureFiles[i],buffer);
		tileTextures[i]=NULL;
	}
	return 0;
}

rpg_map* rpg_parseMap(char* path){
	rpg_map* map;
	char layerPath[512];
	SDL_Surface* surface;
	int x,y,i;
	Uint32* pixels;
	Uint32 pixel;
	rpg_tile* tile;
	int tileId;

	//map=rpg_createMap(surface->w,surface->h,2);
	map=rpg_createMap(5,5,2);
	
	for(i=0;i<2;i++){
		sprintf(layerPath,"%s/layer%d.png",path,i+1);

		printf("Loading map file %s...",layerPath);
		//open map files
		surface=IMG_Load(layerPath);
		if(surface==NULL){
			fprintf(stderr,"\nUnable to load map file \"%s\": %s\n",layerPath,IMG_GetError());
			return NULL;
		}
		if(surface->format->BytesPerPixel!=4){
			fprintf(stderr,"\nUnable to load map file \"%s\": Wrong format\n",layerPath);
			return NULL;
		}

		pixels=surface->pixels;
		printf("done.\n");

		for(y=0;y<surface->h;y++){
			for(x=0;x<surface->w;x++){
				pixel=pixels[y*surface->w+x];
				//printf("Hex. %x\n",pixel);
				tile=map->tiles+y*map->width+x;
				tileId=(pixel & 0x00003fff);
				tile->collision=(pixel & 0x00010000) >> 16;
				rpg_loadTileTexture(tile,tileId,i);
			}
		}
		SDL_FreeSurface(surface);
	}


	return map;
}

void rpg_freeTiletable(){
	int i;
	for(i=tileTypes;i>0;i--){
		if(tileTextureFiles[i]){
			free(tileTextureFiles[i]);
		}
		if(tileTextures[i]){
			SDL_DestroyTexture(tileTextures[i]);
		}
	}
	free(tileTextureFiles);
	free(tileTextures);
}
