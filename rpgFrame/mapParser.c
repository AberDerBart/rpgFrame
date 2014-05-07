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
	char* fields[3];

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
	tileTextures=malloc((lines+1)*sizeof(rpg_tileTexture*));
	tileTypes=lines;
	tileTextureFiles[0]=NULL;
	tileTextures[0]=NULL;

	for(i=1;i<=lines+1;i++){
		tileTextures[i]=malloc(sizeof(rpg_tileTexture));
		tileTextures[i]->frameTime=0;
		tileTextures[i]->frames=1;
		tileTextures[i]->texture[0]=NULL;
		tileTextures[i]->texture[1]=NULL;
		tileTextures[i]->texture[2]=NULL;
		tileTextures[i]->texture[3]=NULL;

		fgets(buffer,512,tableFile);
		buffer[strlen(buffer)-1]=0;

		fields[0]=buffer;
		fields[1]=buffer;
		while(*fields[1] && *fields[1]!='\t') fields[1]++;

		if(*fields[1]){
			*fields[1]='\0';
			fields[1]++;
			fields[2]=fields[1];
			
			while(*fields[2] && *fields[2]!='\t') fields[2]++;

			if(*fields[2]){
				*fields[2]='\0';
				fields[2]++;
				tileTextures[i]->frameTime=atoi(fields[2]);
			}

			tileTextures[i]->frames=atoi(fields[1]);
		}

		tileTextureFiles[i]=malloc((strlen(buffer)+1)*sizeof(char*));
		strcpy(tileTextureFiles[i],buffer);
	}
	return 0;
}

rpg_map* rpg_parseMap(char* path){
	rpg_map* map;
	char layerPath[512];
	SDL_Surface* surface;
	SDL_Surface* tmpSurface;
	int x,y,i;
	Uint32* pixels;
	Uint32 pixel;
	rpg_tile* tile;
	int tileId;
	rpg_tileTextureRotation rot;
	SDL_PixelFormat format;

	sprintf(layerPath,"%s/base.bmp",path);

	printf("Loading event file %s...",layerPath);

	tmpSurface=IMG_Load(layerPath);
	if(tmpSurface==NULL){
		fprintf(stderr,"\nUnable to load map file \"%s\": %s\n",layerPath,IMG_GetError());
		return NULL;
	}
	if(tmpSurface->format->BytesPerPixel!=4){
		 fprintf(stderr,"\nUnable to load map file \"%s\": Wrong format\n",layerPath);
		 return NULL;
	}

	format.format=SDL_PIXELFORMAT_ARGB8888;
	format.palette=NULL;
	format.BitsPerPixel=32;
	format.BytesPerPixel=4;
	format.Rmask=0x00ff0000;
	format.Gmask=0x0000ff00;
	format.Bmask=0x000000ff;
	format.Amask=0xff000000;
	
	surface=SDL_ConvertSurface(tmpSurface,&format,0);

	SDL_FreeSurface(tmpSurface);

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
		tmpSurface=IMG_Load(layerPath);
		if(tmpSurface==NULL){
			fprintf(stderr,"\nUnable to load map file \"%s\": %s\n",layerPath,IMG_GetError());
			return NULL;
		}
		if(tmpSurface->format->BytesPerPixel!=4){
			fprintf(stderr,"\nUnable to load map file \"%s\": Wrong format\n",layerPath);
			return NULL;
		}

		surface=SDL_ConvertSurface(tmpSurface,&format,0);

		SDL_FreeSurface(tmpSurface);

		pixels=surface->pixels;
		printf("done.\n");

		for(y=0;y<surface->h;y++){
			for(x=0;x<surface->w;x++){
				pixel=pixels[y*surface->w+x];
				//printf("Hex. %x\n",pixel);
				tile=map->tiles+y*map->width+x;
				rot=((pixel & 0x00c00000) >> 22);
				tile->rot[i]=rot;
				tileId=(pixel & 0x003fffff);
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
			rpg_freeTileTexture(tileTextures[i]);
		}
	}
	//free(tileTextureFiles);
	//free(tileTextures);
}
