#include "gui.h"
#include "globals.h"
#include <SDL2/SDL_image.h>

rpg_guiTextStyle* rpg_createGuiTextStyle(rpg_guiStyle* baseStyle,char* font_name,int font_size){
	rpg_guiTextStyle* style;
	style=malloc(sizeof(rpg_guiTextStyle));
	style->baseStyle=baseStyle;
	style->guiRect.x=25;
	style->guiRect.y=25;
	style->guiRect.w=200;
	style->guiRect.h=100;
	style->font=TTF_OpenFont(font_name,font_size);
	if(!style->font){
		fprintf(stderr,"Could not load font %s: %s\n",font_name,TTF_GetError());
		free(style);
		return NULL;
	}
	style->textColor.r=0;
	style->textColor.g=0;
	style->textColor.b=0;
	return style;
}

void rpg_drawTextGui(rpg_guiTextStyle* style,char* text){
	SDL_Surface* textSurface;
	SDL_Rect rect;

	rpg_drawGuiFrame(style->baseStyle,style->guiRect);
	textSurface=TTF_RenderText_Solid(style->font,text,style->textColor);

	rect=style->guiRect;
	rect.w=textSurface->w;
	rect.h=textSurface->h;

	SDL_RenderCopy(render,SDL_CreateTextureFromSurface(render,textSurface),NULL,&rect);
}

void rpg_drawGuiFrame(rpg_guiStyle* baseStyle,SDL_Rect guiRect){
	SDL_Rect rect;

	rect.w=baseStyle->bLeft;
	rect.h=baseStyle->bTop;
	rect.x=guiRect.x - rect.w;
	rect.y=guiRect.y - rect.h;
	SDL_RenderCopy(render,baseStyle->top_left,NULL,&rect);

	rect.w=baseStyle->bRight;
	rect.h=baseStyle->bTop;
	rect.x=guiRect.x + guiRect.w;
	rect.y=guiRect.y - rect.h;
	SDL_RenderCopy(render,baseStyle->top_right,NULL,&rect);

	rect.w=baseStyle->bLeft;
	rect.h=baseStyle->bBottom;
	rect.x=guiRect.x - rect.w;
	rect.y=guiRect.y + guiRect.h;
	SDL_RenderCopy(render,baseStyle->bottom_left,NULL,&rect);

	rect.w=baseStyle->bRight;
	rect.h=baseStyle->bBottom;
	rect.x=guiRect.x + guiRect.w;
	rect.y=guiRect.y + guiRect.h;
	SDL_RenderCopy(render,baseStyle->bottom_right,NULL,&rect);

	if(baseStyle->format==STRETCH){
		rect.w=guiRect.w;
		rect.h=baseStyle->bTop;
		rect.x=guiRect.x;
		rect.y=guiRect.y - rect.h;
		SDL_RenderCopy(render,baseStyle->top,NULL,&rect);

		rect.w=baseStyle->bLeft;
		rect.h=guiRect.h;
		rect.x=guiRect.x - rect.w;
		rect.y=guiRect.y;
		SDL_RenderCopy(render,baseStyle->left,NULL,&rect);

		rect.w=baseStyle->bRight;
		rect.h=guiRect.h;
		rect.x=guiRect.x + guiRect.w;
		rect.y=guiRect.y;
		SDL_RenderCopy(render,baseStyle->right,NULL,&rect);

		rect.w=guiRect.w;
		rect.h=baseStyle->bTop;
		rect.x=guiRect.x;
		rect.y=guiRect.y + guiRect.h;
		SDL_RenderCopy(render,baseStyle->bottom,NULL,&rect);

		rect.w=guiRect.w;
		rect.h=guiRect.h;
		rect.x=guiRect.x;
		rect.y=guiRect.y;
		SDL_RenderCopy(render,baseStyle->center,NULL,&rect);
	}

}

SDL_Texture* loadTexture(char* path){
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface=IMG_Load(path);
	if(surface==NULL){
		fprintf(stderr,"\nUnable to load texture file \"%s\": %s\n",path,IMG_GetError());
		return NULL;
	}

	texture=SDL_CreateTextureFromSurface(render,surface);
	SDL_FreeSurface(surface);

	return texture;
}

rpg_guiStyle* rpg_loadGuiStyle(char* path,rpg_guiFormat format){
	rpg_guiStyle* style;
	char loadPath[512];

	style=malloc(sizeof(rpg_guiStyle));
	style->format=format;

	sprintf(loadPath,"%s/center.png",path);
	style->center=loadTexture(loadPath);
	if(!style->center){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/left.png",path);
	style->left=loadTexture(loadPath);
	if(!style->left){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/right.png",path);
	style->right=loadTexture(loadPath);
	if(!style->right){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/top.png",path);
	style->top=loadTexture(loadPath);
	if(!style->top){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/bottom.png",path);
	style->bottom=loadTexture(loadPath);
	if(!style->bottom){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/top_left.png",path);
	style->top_left=loadTexture(loadPath);
	if(!style->top_left){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/top_right.png",path);
	style->top_right=loadTexture(loadPath);
	if(!style->top_right){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/bottom_left.png",path);
	style->bottom_left=loadTexture(loadPath);
	if(!style->bottom_left){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/bottom_right.png",path);
	style->bottom_right=loadTexture(loadPath);
	if(!style->bottom_right){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	return style;
}

void rpg_freeGuiStyle(rpg_guiStyle* style){
	if(style->center){
		SDL_DestroyTexture(style->center);
	}
	if(style->left){
		SDL_DestroyTexture(style->left);
	}
	if(style->right){
		SDL_DestroyTexture(style->right);
	}
	if(style->top){
		SDL_DestroyTexture(style->top);
	}
	if(style->bottom){
		SDL_DestroyTexture(style->bottom);
	}
	if(style->top_left){
		SDL_DestroyTexture(style->top_left);
	}
	if(style->top_right){
		SDL_DestroyTexture(style->top_right);
	}
	if(style->bottom_left){
		SDL_DestroyTexture(style->bottom_left);
	}
	if(style->bottom_right){
		SDL_DestroyTexture(style->bottom_right);
	}
	free(style);
}
