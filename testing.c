#include <stdio.h>
#include <SDL2/SDL.h>
#include "rpgFrame/all.h"

void event_1(){
	printf("hallo welt\n");
}

void event_2(){
	printf("blubb\n");
	rpg_setGui(NULL);
}

int main(){
	rpg_scene scene;

	if(rpg_init()){
		return -1;
	}

	if(rpg_setTiletable("tiles.txt")){
		return -1;
	}

	scene.map=rpg_parseMap("testmap");
	scene.map->chars=list_create();

	rpg_protagonist=rpg_createCharacter("img/sprites/char.png");
	rpg_character_setMap(rpg_protagonist,scene.map,2,2);
	scene.focus=rpg_protagonist;
	rpg_curScene=&scene;
	

	/*rect.x=25;
	rect.y=300;
	rect.w=190;
	rect.h=155;
	guiStyle=rpg_loadGuiStyle("img/gui",STRETCH,"/usr/share/fonts/truetype/freefont/FreeSerif.ttf",20);

	actions=malloc(3*sizeof(rpg_action));
	actions[0].text="Mama";
	actions[1].text="Blubb";
	actions[2].text="Ball";
	actions[0].function=&event_1;
	actions[1].function=&event_2;
	actions[2].function=&event_1;

	rpg_setGui(rpg_createChoiceGui(guiStyle,actions,rect,3));

	rpg_bindKey(SDLK_RETURN,&rpg_guiSelect);
	rpg_bindKey(SDLK_w,&rpg_guiUp);
	rpg_bindKey(SDLK_s,&rpg_guiDown);*/

	rpg_mainloop();

	rpg_close();
}
