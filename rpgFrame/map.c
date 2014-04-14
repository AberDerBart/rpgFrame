#include "map.h"
#include "globals.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

rpg_map* rpg_createMap(int w, int h){
	rpg_map* map;
	int x,y;

	map=malloc(sizeof(rpg_map));
	map->height=h;
	map->width=w;
	map->tiles=malloc(w*h*sizeof(rpg_tile));

	for(y=0;y<h;y++){
		for(x=0;x<w;x++){
			map->tiles[w*y+x].texture=NULL;
			map->tiles[w*y+x].collision=NONE;
			map->tiles[w*y+x].tileId=0;
		}
	}

	return map;
}

int rpg_drawMap(rpg_map* map){
	int x,y;
	SDL_Rect rect;
	rect.w=TILE_SIZE;
	rect.h=TILE_SIZE;
	for(y=0;y<map->height;y++){
		for(x=0;x<map->width;x++){
			rect.x=x*TILE_SIZE;
			rect.y=y*TILE_SIZE;
			SDL_RenderCopy(render,map->tiles[map->width*y+x].texture,NULL,&rect);
		}
	}
	SDL_RenderPresent(render);
	return 0;
}

