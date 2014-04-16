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
	SDL_Surface* surface;
	int x,y;
	Uint32* pixels;
	Uint32 pixel;
	rpg_tile* tile;

	//open map file
	surface=IMG_Load(path);
	if(surface==NULL){
		fprintf(stderr,"Unable to load map file \"%s\": %s\n",path,IMG_GetError());
		return NULL;
	}
	if(surface->format->BytesPerPixel!=4){
		fprintf(stderr,"Unable to load map file \"%s\": Wrong format\n",path);
		return NULL;
	}

	map=rpg_createMap(surface->w,surface->h);

	pixels=surface->pixels;

	for(y=0;y<surface->h;y++){
		for(x=0;x<surface->w;x++){
			pixel=pixels[y*surface->w+x];
			printf("Hex. %x\n",pixel);
			tile=map->tiles+y*map->width+x;
			tile->collision=(pixel & 0x00010000) >> 16;
			tile->tileId=(pixel & 0x00003fff);
			rpg_loadTileTexture(tile,tile->tileId);
		}
	}

	SDL_FreeSurface(surface);

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
