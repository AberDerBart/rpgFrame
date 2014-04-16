#include <stdio.h>
#include <SDL2/SDL.h>
#include "rpgFrame/window.h"
#include "rpgFrame/map.h"
#include "rpgFrame/mapParser.h"
#include "rpgFrame/mainloop.h"
#include "rpgFrame/character.h"
#include "rpgFrame/scene.h"
#include "rpgFrame/list.h"

int main(){
	rpg_scene scene;

	if(rpg_init()){
		return -1;
	}

	if(rpg_setTiletable("tiles.txt")){
		return -1;
	}

	scene.map=rpg_parseMap("testmap.png");
	scene.chars=list_create();

	list_insert(scene.chars,rpg_createCharacter("img/char.png"));
	rpg_protagonist=scene.chars->next->item;
	scene.focus=rpg_protagonist;
	rpg_curScene=&scene;
	
	rpg_protagonist->x=2;
	rpg_protagonist->y=2;

	rpg_drawScene(&scene);

	rpg_mainloop();

	rpg_close();
}
