#include "d12.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include "rpgFrame/window.h"
#include "rpgFrame/map.h"
#include "rpgFrame/mapParser.h"
#include "rpgFrame/mainloop.h"
#include "rpgFrame/character.h"

int main(){
	rpg_map* map;

	if(rpg_init()){
		return -1;
	}

	if(rpg_setTiletable("tiles.txt")){
		return -1;
	}

	map=rpg_parseMap("testmap.png");
	if(!map){
		return -1;
	}

	rpg_protagonist=rpg_createCharacter("img/char.png");
	if(!rpg_protagonist){
		return -2;
	}

	rpg_drawMap(map);

	rpg_drawCharacter(rpg_protagonist);

	rpg_mainloop();

	rpg_close();
}
