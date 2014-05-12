#include "events.h"
#include "map.h"
#include "mainloop.h"

int rpg_checkEvent_walkTo(rpg_direction dir){
	int x,y,eventId;
	rpg_tile* tile;
	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	tile=rpg_getMapTile(rpg_curScene->map,x,y,dir);
	
	if(tile==NULL){
		return -1;
	}

	eventId=tile->eventId;

	if(eventId==0){
		return 0;
	}else{
		if(!rpg_events){
			fprintf(stderr,"Could not parse Event: No eventlist\n");
			return -1;
		}
		
		if(!rpg_events[eventId].walkTo){
			return 0;
		}

		rpg_events[eventId].walkTo();
	}
	return 0;
}

int rpg_checkEvent_stand(){
	int x,y,eventId;
	rpg_tile* tile;
	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	tile=rpg_getMapTile(rpg_curScene->map,x,y,D_NONE);

	eventId=tile->eventId;

	if(eventId==0){
		return 0;
	}else{
		if(!rpg_events){
			fprintf(stderr,"Could not parse Event: No eventlist\n");
			return -1;
		}
		
		if(!rpg_events[eventId].standOn){
			return 0;
		}

		rpg_events[eventId].standOn();
	}
	return 0;
}
