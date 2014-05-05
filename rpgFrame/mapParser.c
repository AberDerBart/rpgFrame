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
	for(i=1;i<=lines+1;i++){
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

	sprintf(layerPath,"%s/base.bmp",path);

	printf("Loading event file %s...",layerPath);

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

	map=rpg_createMap(surface->w,surface->h,4);

	for(y=0;y<surface->h;y++){
		for(x=0;x<surface->w;x++){
			pixel=pixels[y*surface->w+x];
			tile=map->tiles+y*map->width+x;
			tile->eventId=(pixel & 0x0000ffff);
			tile->collision=(pixel & 0x00ff0000) >> 16;
		}
	}

	printf("done.\n");

	
	for(i=0;i<4;i++){
		sprintf(layerPath,"%s/layer%d.bmp",path,i);

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
