#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "globals.h"
#include "mapParser.h"

SDL_Window* win;
SDL_Surface* winSurf;

int width,height;

int rpg_init(){
	width=640;
	height=480;
	win=NULL;
	winSurf=NULL;

	if(SDL_Init(SDL_INIT_VIDEO)<0){
		fprintf(stderr,"Could not initialize SDL: %s\n",SDL_GetError());
		return -1;
	}

	win=SDL_CreateWindow("rpgFrame",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,height, SDL_WINDOW_SHOWN);
	if(win==NULL){
		fprintf(stderr,"Could not create SDL-window: %s\n",SDL_GetError());
		return -1;
	}

	render=SDL_CreateRenderer(win,-1,SDL_RENDERER_SOFTWARE);
	if(render==NULL){
		fprintf(stderr,"Could not initialize SDL-renderer: %s\n",SDL_GetError());
		return -1;
	}
	SDL_SetRenderDrawColor(render,0xff,0xff,0xff,0xff);
	if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)){
		fprintf(stderr,"Could not initialize png loading: %s\n",SDL_GetError());
		return -1;
	}

	//winSurf=SDL_GetWindowSurface(win);
	return 0;
}

int rpg_close(){
	rpg_freeTiletable();
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(win);
	
	win=NULL;
	render=NULL;

	IMG_Quit();
	SDL_Quit();

	return 0;
}
