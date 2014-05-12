#include "scene.h"
#include "window.h"
#include "globals.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "gui.h"


void rpg_drawScene(rpg_scene* scene){
	if(scene->focus){
		scene->off_x=scene->focus->x*TILE_SIZE+scene->focus->step_x+TILE_SIZE/2-rpg_width/2;
		scene->off_y=scene->focus->y*TILE_SIZE+scene->focus->step_y+TILE_SIZE/2-rpg_height/2;
	}else{
		scene->off_x=0;
		scene->off_y=0;
	}
	rpg_drawMap(scene->map);
	list_forEach(scene->map->chars,(void (*)(void*)) &rpg_drawCharacter);
}

void rpg_setFocus(rpg_scene* scene,rpg_character* focus){
	scene->focus=focus;
	if(!list_contains(scene->map->chars,focus)){
		list_insert(scene->map->chars,focus);
	}
}
