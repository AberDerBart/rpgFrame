#include "map.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "mainloop.h"

rpg_map* rpg_createMap(int w, int h, int layers){
	rpg_map* map;
	int x,y,i;

	map=malloc(sizeof(rpg_map));
	map->height=h;
	map->width=w;
	map->layers=layers;
	map->tiles=malloc(w*h*sizeof(rpg_tile));

	for(y=0;y<h;y++){
		for(x=0;x<w;x++){
			map->tiles[w*y+x].collision=NONE;
			map->tiles[w*y+x].tileId=0;
			map->tiles[w*y+x].eventId=0;
			map->tiles[w*y+x].textures=malloc(layers*sizeof(rpg_tileTexture*));
			map->tiles[w*y+x].rot=malloc(layers*sizeof(rpg_tileTextureRotation));
			for(i=0;i<layers;i++){
				map->tiles[w*y+x].textures[i]=NULL;
				map->tiles[w*y+x].rot[i]=R0;
			}
		}
	}

	return map;
}

int rpg_drawMap(rpg_map* map){
	int x,y,i;
	int frames;
	int frameTime;
	Uint32 curTime;

	curTime=rpg_getGameTime();

	SDL_Rect rect;
	SDL_Rect texRect;
	texRect.x=0;
	texRect.y=0;
	texRect.w=TILE_SIZE;
	texRect.h=TILE_SIZE;
	rect.w=TILE_SIZE;
	rect.h=TILE_SIZE;
	for(y=0;y<map->height;y++){
		for(x=0;x<map->width;x++){
			rect.x=x*TILE_SIZE-rpg_curScene->off_x;
			rect.y=y*TILE_SIZE-rpg_curScene->off_y;
			rect.h=TILE_SIZE;
			rect.w=TILE_SIZE;
			for(i=0;i<map->layers;i++){
				if(map->tiles[map->width*y+x].textures[i]){
					frames=map->tiles[map->width*y+x].textures[i]->frames;
					frameTime=map->tiles[map->width*y+x].textures[i]->frameTime;
					if(frameTime){
						texRect.x=TILE_SIZE*(curTime/frameTime%frames);
					}else{
						texRect.x=0;
					}
					SDL_RenderCopy(render,map->tiles[map->width*y+x].textures[i]->texture[map->tiles[map->width*y+x].rot[i]],&texRect,&rect);
				}
			}
		}
	}
	return 0;
}

rpg_tile* rpg_getMapTile(rpg_map* map,int x,int y,rpg_direction dir){
	if(dir==D_UP){
		y--;
	}else if(dir==D_LEFT){
		x--;
	}else if(dir==D_RIGHT){
		x++;
	}else if(dir==D_DOWN){
		y++;
	}
	if(x<0 || y<0 || x>=map->width || y>=map->height){
		return NULL;
	}else{
		return map->tiles+x+y*map->width;
	}
}
