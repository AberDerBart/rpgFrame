#include <stdio.h>
#include <SDL2/SDL.h>
#include "rpgFrame/window.h"
#include "rpgFrame/map.h"
#include "rpgFrame/mapParser.h"
#include "rpgFrame/mainloop.h"
#include "rpgFrame/character.h"
#include "rpgFrame/scene.h"
#include "rpgFrame/list.h"
#include "rpgFrame/events.h"
#include "rpgFrame/gui.h"
#include "rpgFrame/globals.h"

void event_1(){
	printf("hallo welt\n");
}

void event_2(){
	printf("blubb\n");
	rpg_setGui(NULL);
}

int main(){
	rpg_scene scene;
	rpg_events=malloc(2*sizeof(rpg_event));
	rpg_eventCount=2;
	rpg_events[1].standOn=&event_1;
	rpg_action* actions;
	SDL_Rect rect;

	if(rpg_init()){
		return -1;
	}

	if(rpg_setTiletable("tiles.txt")){
		return -1;
	}

	scene.map=rpg_parseMap("testmap");
	scene.chars=list_create();

	list_insert(scene.chars,rpg_createCharacter("img/sprites/char.png"));
	rpg_protagonist=scene.chars->next->item;
	list_insert(scene.chars,rpg_createCharacter("img/sprites/char.png"));
	scene.focus=rpg_protagonist;
	rpg_curScene=&scene;
	
	rpg_protagonist->x=2;
	rpg_protagonist->y=2;

	rect.x=25;
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

	rpg_mainloop();

	rpg_close();
}
