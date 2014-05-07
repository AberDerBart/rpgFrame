#include "tile.h"
#include "globals.h"
#include <SDL2/SDL_image.h>

int rotTexture(rpg_tile*,int);

int rpg_loadTileTexture(rpg_tile* tile,int tileID,int layer){
	SDL_Surface* tmpSurface;
	SDL_Surface* surface[4];
	SDL_Texture* tex;
	SDL_PixelFormat format;
	char* path;
	int x,y;
	int w,h;
	Uint32* rotPixels[4];

	if(tileID>tileTypes){
		fprintf(stderr,"Unable to load texture: invalid tile ID\n");
		return -1;
	}
	if(tileID==0){
		tile->textures[layer]=NULL;
		return;
	}
	
	if(tileTextures[tileID]->texture[0]==NULL){
		printf("loading texture #%d: %s... ",tileID,tileTextureFiles[tileID]);
		path=tileTextureFiles[tileID];

		tmpSurface=IMG_Load(path);
		if(tmpSurface==NULL){
			fprintf(stderr,"\nUnable to load texture file \"%s\": %s\n",path,IMG_GetError());
			return -1;
		}

		format.format=SDL_PIXELFORMAT_ARGB8888;
		format.palette=NULL;
		format.BitsPerPixel=32;
		format.BytesPerPixel=4;
		format.Rmask=0x00ff0000;
		format.Gmask=0x0000ff00;
		format.Bmask=0x000000ff;
		format.Amask=0xff000000;

		surface[0]=SDL_ConvertSurface(tmpSurface,&format,0);
		surface[1]=SDL_ConvertSurface(tmpSurface,&format,0);
		surface[2]=SDL_ConvertSurface(tmpSurface,&format,0);
		surface[3]=SDL_ConvertSurface(tmpSurface,&format,0);

		rotPixels[0]=surface[0]->pixels;
		rotPixels[1]=surface[1]->pixels;
		rotPixels[2]=surface[2]->pixels;
		rotPixels[3]=surface[3]->pixels;
	
		w=tmpSurface->w;
		h=tmpSurface->h;

		SDL_FreeSurface(tmpSurface);

		if(w==h){
			for(y=0;y<h;y++){
				for(x=0;x<w;x++){
					rotPixels[1][x*w+w-y-1]=rotPixels[0][y*w+x];	
					rotPixels[2][w*h-y*w-x-1]=rotPixels[0][y*w+x];
					rotPixels[3][h*w-w+y-w*x]=rotPixels[0][y*w+x];
				}
			}
		}

		tileTextures[tileID]->texture[0]=SDL_CreateTextureFromSurface(render,surface[0]);
		tileTextures[tileID]->texture[1]=SDL_CreateTextureFromSurface(render,surface[1]);
		tileTextures[tileID]->texture[2]=SDL_CreateTextureFromSurface(render,surface[2]);
		tileTextures[tileID]->texture[3]=SDL_CreateTextureFromSurface(render,surface[3]);

		SDL_FreeSurface(surface[0]);
		SDL_FreeSurface(surface[1]);
		SDL_FreeSurface(surface[2]);
		SDL_FreeSurface(surface[3]);

		printf("done.\n");
	}

	tile->textures[layer]=tileTextures[tileID];

	return 0;
}

void rpg_freeTileTexture(rpg_tileTexture* tex){
	if(tex->texture){
	//	SDL_DestroyTexture(tex->texture);
	}
	//free(tex);
}
