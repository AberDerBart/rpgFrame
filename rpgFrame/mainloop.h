#ifndef MAINLOOP_H
#define MAINLOOP_H

#include "keylist.h"
#include "character.h"
#include "list.h"
#include "scene.h"

genericList* movedObjectsList;
rpg_scene* rpg_curScene;

int rpg_mainloop();
void rpg_quit();
void rpg_redraw();
void rpg_freeze(int);
long rpg_getGameTime();

#endif
