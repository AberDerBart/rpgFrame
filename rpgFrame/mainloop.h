#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "keylist.h"
#include "character.h"
#include "list.h"
#include "scene.h"

typedef struct{
	rpg_direction dir;
	rpg_direction nextDir;
	double speed;
	Uint32 startTime;
	rpg_character* c;
} movedObject;

genericList* movedObjectsList;
rpg_scene* rpg_curScene;

int rpg_mainloop();
void rpg_quit();
void rpg_redraw();

#endif
