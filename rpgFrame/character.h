#ifndef CHARAKTER_H
#define CHARAKTER_H

typedef enum{
	UP,
	DOWN,
	LEFT,
	RIGHT
} rpg_direction;

typedef struct{
	int x;
	int y;
	int step_x;
	int step_y;
	
} rpg_character;

rpg_character* rpg_protagonist;

void rpg_setProtagonst(rpg_character*);

void rpg_drawCharacter(rpg_character);

void rpg_moveCharacter(rpg_character*, rpg_direction);

void rpg_moveProtagonist(void*);

#endif
