#ifndef GUI_H
#define GUI_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef enum{
	TEXT,
	CHOICE,
	BASIC
} rpg_guiType;

typedef enum{
	REPEAT,
	STRETCH
} rpg_guiFormat;

typedef struct{
	SDL_Texture* center;
	SDL_Texture* left;
	SDL_Texture* right;
	SDL_Texture* top;
	SDL_Texture* bottom;
	SDL_Texture* top_left;
	SDL_Texture* top_right;
	SDL_Texture* bottom_left;
	SDL_Texture* bottom_right;

	SDL_Texture* sel_center;
	SDL_Texture* sel_left;
	SDL_Texture* sel_right;
	SDL_Texture* sel_top;
	SDL_Texture* sel_bottom;
	SDL_Texture* sel_top_left;
	SDL_Texture* sel_top_right;
	SDL_Texture* sel_bottom_left;
	SDL_Texture* sel_bottom_right;

	rpg_guiFormat format;
	int bLeft;
	int bRight;
	int bTop;
	int bBottom;
	
	int selBLeft;
	int selBRight;
	int selBTop;
	int selBBottom;

	int selBILeft;
	int selBIBottom;
	int selBITop;
	int selBIRight;

	TTF_Font* font;
	SDL_Color textColor;
} rpg_guiStyle;

typedef struct{
	char* text;
} rpg_guiText;

typedef struct{
	void (*function)();
	char* text;
} rpg_action;

typedef struct{
	rpg_action* actions;
	int actionCount;
	int selectedAction;
} rpg_guiChoice;

typedef struct{
	rpg_guiStyle* style;
	rpg_guiType type;
	SDL_Texture* texture;
	SDL_Surface* surface;
	SDL_Rect rect;
	union{
		rpg_guiText text;
		rpg_guiChoice choice;
	} detail;
} rpg_gui;

rpg_gui* currentGui;

typedef struct rpg_menu rpg_menu;

void rpg_setGui(rpg_gui*);
void rpg_drawGuiFrame(rpg_guiStyle*,SDL_Rect);
void rpg_drawGuiSelFrame(rpg_guiStyle*,SDL_Rect);
void rpg_drawGui();
rpg_guiStyle* rpg_loadGuiStyle(char*,rpg_guiFormat,char*,int);
void rpg_freeGuiStyle(rpg_guiStyle*);
SDL_Texture* rpg_createGuiBG(rpg_gui*);
rpg_gui* rpg_createChoiceGui(rpg_guiStyle*,rpg_action*,SDL_Rect,int);
rpg_gui* rpg_createTextGui(rpg_guiStyle*,char*,SDL_Rect);
rpg_gui* rpg_createBasicGui(rpg_guiStyle*,SDL_Rect);
void rpg_redrawGui(rpg_gui*);

void rpg_guiDown();
void rpg_guiUp();
void rpg_guiSelect();

#endif
