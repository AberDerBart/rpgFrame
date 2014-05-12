#ifndef EVENTS_H
#define EVENTS_H
#include "character.h"

typedef struct{
	void (*standOn)();
	void (*walkTo)();
} rpg_event;

rpg_event* rpg_events;
int rpg_eventCount;

int rpg_checkEvent_walkTo(rpg_direction);
int rpg_checkEvent_stand();

#endif
