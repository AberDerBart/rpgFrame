#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "keylist.h"
#include "character.h"
#include "list.h"

typedef struct{
	rpg_direction dir;
	double speed;
	Uint32 startTime;
	rpg_character* c;
} movedObject;

genericList* movedObjectsList;

int rpg_mainloop();
void rpg_quit(void*);
void rpg_redraw();

#endif
