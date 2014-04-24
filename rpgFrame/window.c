#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "globals.h"
#include "mapParser.h"
#include "window.h"

SDL_Window* win;


int rpg_init(){
	rpg_width=640;
	rpg_height=480;
	win=NULL;

	if(SDL_Init(SDL_INIT_VIDEO)<0){
		fprintf(stderr,"Could not initialize SDL: %s\n",SDL_GetError());
		return -1;
	}

	win=SDL_CreateWindow("rpgFrame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, rpg_width,rpg_height, SDL_WINDOW_SHOWN);
	if(win==NULL){
		fprintf(stderr,"Could not create SDL-window: %s\n",SDL_GetError());
		return -1;
	}

	render=SDL_CreateRenderer(win,-1,SDL_RENDERER_SOFTWARE);
	if(render==NULL){
		fprintf(stderr,"Could not initialize SDL-renderer: %s\n",SDL_GetError());
		return -1;
	}
	SDL_SetRenderDrawColor(render,0x00,0x00,0x00,0x00);
	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		fprintf(stderr,"Could not initialize png loading: %s\n",SDL_GetError());
		return -1;
	}

	if(TTF_Init() == -1){
		fprintf(stderr,"Could not initialize TTF: %s\n",SDL_GetError());
		return -1;
	}

	return 0;
}

int rpg_close(){
	rpg_freeTiletable();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	
	win=NULL;
	render=NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}
