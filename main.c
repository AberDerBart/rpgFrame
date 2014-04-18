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

void event_1(){
	printf("hallo welt\n");
}

int main(){
	rpg_scene scene;
	rpg_events=malloc(2*sizeof(rpg_event));
	rpg_eventCount=2;
	rpg_events[1].standOn=&event_1;

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

	rpg_mainloop();

	rpg_close();
}
