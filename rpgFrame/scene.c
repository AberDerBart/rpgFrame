#include "scene.h"
#include "window.h"
#include "globals.h"
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include "gui.h"


void rpg_drawScene(rpg_scene* scene){
	scene->off_x=scene->focus->x*TILE_SIZE+scene->focus->step_x+TILE_SIZE/2-rpg_width/2;
	scene->off_y=scene->focus->y*TILE_SIZE+scene->focus->step_y+TILE_SIZE/2-rpg_height/2;
	rpg_drawMap(scene->map);
	list_forEach(scene->chars,(void (*)(void*)) &rpg_drawCharacter);

	/*if(!gui){
		gui=rpg_loadGuiStyle("img/gui",STRETCH);
		gui->bLeft=16;
		gui->bRight=16;
		gui->bTop=16;
		gui->bBottom=16;
		tGui=rpg_createGuiTextStyle(gui,"/usr/share/fonts/truetype/freefont/FreeSans.ttf",28);
		tGui->baseStyle=gui;
		tGui->guiRect.x=25;
		tGui->guiRect.y=325;
		tGui->guiRect.w=590;
		tGui->guiRect.h=130;
	}

	rpg_drawTextGui(tGui,"Was genau heißt nochmal passend?");*/

	SDL_RenderPresent(render);
}

void rpg_setFocus(rpg_scene* scene,rpg_character* focus){
	scene->focus=focus;
}
