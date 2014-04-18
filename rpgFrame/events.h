#ifndef EVENTS_H
#define EVENTS_H

typedef struct{
	void (*standOn)();
} rpg_event;

rpg_event* rpg_events;
int rpg_eventCount;

int rpg_checkEvent_stand();

#endif
