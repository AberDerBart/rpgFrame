#ifndef GUI_H
#define GUI_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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
	rpg_guiFormat format;
	int bLeft;
	int bRight;
	int bTop;
	int bBottom;
} rpg_guiStyle;

typedef struct{
	rpg_guiStyle* baseStyle;
	SDL_Rect guiRect;
	SDL_Color textColor;
	TTF_Font* font;
} rpg_guiTextStyle;

void rpg_drawGuiFrame(rpg_guiStyle*,SDL_Rect);
void rpg_drawTextGui(rpg_guiTextStyle*,char*);
rpg_guiStyle* rpg_loadGuiStyle(char*,rpg_guiFormat);
void rpg_freeGuiStyle(rpg_guiStyle*);

#endif
