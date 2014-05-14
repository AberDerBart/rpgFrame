#ifndef STRUCTS_H
#define STRUCTS_H
#include <SDL2/SDL.h>

typedef enum{
	INVALID=-1,
	NONE=0,
	SOLID=1
} collisionType;

typedef enum{
	R0=0,
	R90=1,
	R180=2,
	r270=3
} rpg_tileTextureRotation;

typedef struct{
	SDL_Texture* texture[4];
	int frames;
	int frameTime;
} rpg_tileTexture;

struct rpg_tile{
	rpg_tileTexture** textures;
	rpg_tileTextureRotation* rot;
	collisionType collision;
	int tileId;
	int eventId;
	struct rpg_character* occupant;
};
typedef struct rpg_tile rpg_tile;

struct genericList{
	struct genericList* next;
	void* item;
	struct genericList* prev;
};

typedef struct genericList genericList;


struct rpg_map{
	int height;
	int width;
	int layers;
	struct rpg_tile* tiles;
	genericList* chars;
	struct rpg_event* events;
	int eventCount;
};

typedef struct rpg_map rpg_map; 

struct rpg_event{
	void (*standOn)();
	void (*walkTo)();
};


typedef enum{
	D_NONE=0,
	D_UP=1,
	D_LEFT=2,
	D_DOWN=3,
	D_RIGHT=4
} rpg_direction;

typedef enum{
	NORMAL,
	MOVING
} rpg_characterState;

struct rpg_character{
	int x;
	int y;
	int step_x;
	int step_y;
	int sprite_frames;
	SDL_Texture* texture;
	rpg_characterState state;
	rpg_direction dir;
	struct rpg_tile* tile;
	struct rpg_map* map;
	struct rpg_event event;
};

typedef struct rpg_character rpg_character;

typedef struct{
	rpg_direction dir;
	rpg_direction nextDir;
	double speed;
	Uint32 startTime;
	rpg_character* c;
} movedObject;

typedef struct rpg_event rpg_event;

#endif
