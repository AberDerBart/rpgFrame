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
	char layer1path[512];
	char layer2path[512];
	SDL_Surface* surface_1;
	SDL_Surface* surface_2;
	int x,y;
	Uint32* pixels1;
	Uint32 pixel;
	Uint32* pixels2;
	rpg_tile* tile;
	int tileId;
	
	sprintf(layer1path,"%s/layer1.png",path);
	sprintf(layer2path,"%s/layer2.png",path);

	//open map files
	surface_1=IMG_Load(layer1path);
	if(surface_1==NULL){
		fprintf(stderr,"Unable to load map file \"%s\": %s\n",layer2path,IMG_GetError());
		return NULL;
	}
	if(surface_1->format->BytesPerPixel!=4){
		fprintf(stderr,"Unable to load map file \"%s\": Wrong format\n",layer2path);
		return NULL;
	}

	surface_2=IMG_Load(layer2path);
	if(surface_2==NULL){
		fprintf(stderr,"Unable to load map file \"%s\": %s\n",layer2path,IMG_GetError());
		return NULL;
	}
	if(surface_2->format->BytesPerPixel!=4){
		fprintf(stderr,"Unable to load map file \"%s\": Wrong format\n",layer2path);
		return NULL;
	}
	if(surface_1->h!= surface_2->h || surface_1->w!=surface_2->w){
		fprintf(stderr,"Unable to load maps: Map files have different sizes");
		return NULL;
	}

	map=rpg_createMap(surface_1->w,surface_1->h);

	pixels1=surface_1->pixels;
	pixels2=surface_2->pixels;

	for(y=0;y<surface_1->h;y++){
		for(x=0;x<surface_1->w;x++){
			pixel=pixels1[y*surface_1->w+x];
			//printf("Hex. %x\n",pixel);
			tile=map->tiles+y*map->width+x;
			tileId=(pixel & 0x00003fff);
			tile->collision=(pixel & 0x00010000) >> 16;
			rpg_loadTileTexture(tile,tileId,1);
			
			pixel=pixels2[y*surface_2->w+x];
			tileId=(pixel & 0x00003fff);
			rpg_loadTileTexture(tile,tileId,2);

			
		}
	}

	SDL_FreeSurface(surface_1);
	SDL_FreeSurface(surface_2);

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
