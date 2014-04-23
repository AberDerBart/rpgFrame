#include "gui.h"
#include "globals.h"
#include <SDL2/SDL_image.h>
#include <stdlib.h>


void rpg_drawGui(){
	SDL_Rect rect;

	if(currentGui){
		rpg_drawGuiFrame(currentGui->style,currentGui->rect);
		SDL_RenderCopy(render,currentGui->texture,NULL,&currentGui->rect);
	}
}

void rpg_setGui(rpg_gui* gui){
	currentGui=gui;
}

rpg_gui* rpg_createTextGui(rpg_guiStyle* style,char* text,SDL_Rect rect){
	rpg_gui* gui;
	SDL_Texture* tex;
	SDL_Rect drawRect;

	gui=malloc(sizeof(rpg_gui));
	gui->style=style;
	gui->type=TEXT;
	gui->rect=rect;
	gui->detail.text.text=text;

	gui->surface=TTF_RenderText_Solid(style->font,text,style->textColor);
	gui->texture=rpg_createGuiBG(gui);
	
	tex=SDL_CreateTextureFromSurface(render,gui->surface);

	drawRect.x=0;
	drawRect.y=0;
	drawRect.w=gui->surface->w;
	drawRect.h=gui->surface->h;

	SDL_SetRenderTarget(render,gui->texture);
	SDL_RenderCopy(render,tex,NULL,&drawRect);
	SDL_SetRenderTarget(render,NULL);

	SDL_DestroyTexture(tex);
	
	return gui;
}

rpg_gui* rpg_createChoiceGui(rpg_guiStyle* style,rpg_action* actions,SDL_Rect rect,int actionCount){
	rpg_gui* gui;
	SDL_Texture* tex;
	SDL_Rect drawRect;
	int i;
	
	gui=malloc(sizeof(rpg_gui));
	gui->style=style;
	gui->type=CHOICE;
	gui->rect=rect;
	gui->detail.choice.actions=actions;
	gui->detail.choice.actionCount=actionCount;

	gui->texture=rpg_createGuiBG(gui);

	SDL_SetRenderTarget(render,gui->texture);

	for(i=0;i<actionCount;i++){
		gui->surface=TTF_RenderText_Solid(style->font,actions[i].text,style->textColor);
		tex=SDL_CreateTextureFromSurface(render,gui->surface);
		
		drawRect.x=(rect.w-gui->surface->w)/2;
		drawRect.y=rect.h/actionCount*(i+.5)-gui->surface->h/2;
		drawRect.w=gui->surface->w;
		drawRect.h=gui->surface->h;

		SDL_RenderCopy(render,tex,NULL,&drawRect);
		SDL_DestroyTexture(tex);
	}

	drawRect.x=10;
	drawRect.y=10;
	drawRect.w=gui->rect.w-20;
	drawRect.h=gui->rect.h/actionCount-20;

	rpg_drawGuiSelFrame(gui->style,drawRect);


	SDL_SetRenderTarget(render,NULL);

	return gui;
}

SDL_Texture* rpg_createGuiBG(rpg_gui* gui){
	SDL_Texture* tex;

	tex=NULL;
	tex=SDL_CreateTexture(render,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, gui->rect.w,gui->rect.h);
	
	if(tex){
		SDL_SetRenderTarget(render,tex);
		if(gui->style->format==STRETCH){
			SDL_RenderCopy(render,gui->style->center,NULL,NULL);
		}
		SDL_SetRenderTarget(render,NULL);
	}

	return tex;
}

void rpg_drawGuiSelFrame(rpg_guiStyle* baseStyle,SDL_Rect guiRect){
	SDL_Rect rect;

	rect.w=baseStyle->selBLeft;
	rect.h=baseStyle->selBTop;
	rect.x=guiRect.x - rect.w;
	rect.y=guiRect.y - rect.h;
	SDL_RenderCopy(render,baseStyle->sel_top_left,NULL,&rect);

	rect.w=baseStyle->selBRight;
	rect.h=baseStyle->selBTop;
	rect.x=guiRect.x + guiRect.w;
	rect.y=guiRect.y - rect.h;
	SDL_RenderCopy(render,baseStyle->sel_top_right,NULL,&rect);

	rect.w=baseStyle->selBLeft;
	rect.h=baseStyle->selBBottom;
	rect.x=guiRect.x - rect.w;
	rect.y=guiRect.y + guiRect.h;
	SDL_RenderCopy(render,baseStyle->sel_bottom_left,NULL,&rect);

	rect.w=baseStyle->selBRight;
	rect.h=baseStyle->selBBottom;
	rect.x=guiRect.x + guiRect.w;
	rect.y=guiRect.y + guiRect.h;
	SDL_RenderCopy(render,baseStyle->sel_bottom_right,NULL,&rect);

	if(baseStyle->format==STRETCH){
		rect.w=guiRect.w;
		rect.h=baseStyle->selBTop;
		rect.x=guiRect.x;
		rect.y=guiRect.y - rect.h;
		SDL_RenderCopy(render,baseStyle->sel_top,NULL,&rect);

		rect.w=baseStyle->selBLeft;
		rect.h=guiRect.h;
		rect.x=guiRect.x - rect.w;
		rect.y=guiRect.y;
		SDL_RenderCopy(render,baseStyle->sel_left,NULL,&rect);

		rect.w=baseStyle->selBRight;
		rect.h=guiRect.h;
		rect.x=guiRect.x + guiRect.w;
		rect.y=guiRect.y;
		SDL_RenderCopy(render,baseStyle->sel_right,NULL,&rect);

		rect.w=guiRect.w;
		rect.h=baseStyle->selBTop;
		rect.x=guiRect.x;
		rect.y=guiRect.y + guiRect.h;
		SDL_RenderCopy(render,baseStyle->sel_bottom,NULL,&rect);
	}
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

rpg_guiStyle* rpg_loadGuiStyle(char* path,rpg_guiFormat format,char* font_name,int font_size){
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

	sprintf(loadPath,"%s/sel_center.png",path);
	style->sel_center=loadTexture(loadPath);
	if(!style->sel_center){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_left.png",path);
	style->sel_left=loadTexture(loadPath);
	if(!style->sel_left){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_right.png",path);
	style->sel_right=loadTexture(loadPath);
	if(!style->sel_right){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_top.png",path);
	style->sel_top=loadTexture(loadPath);
	if(!style->sel_top){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_bottom.png",path);
	style->sel_bottom=loadTexture(loadPath);
	if(!style->sel_bottom){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_top_left.png",path);
	style->sel_top_left=loadTexture(loadPath);
	if(!style->sel_top_left){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_top_right.png",path);
	style->sel_top_right=loadTexture(loadPath);
	if(!style->sel_top_right){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_bottom_left.png",path);
	style->sel_bottom_left=loadTexture(loadPath);
	if(!style->sel_bottom_left){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	sprintf(loadPath,"%s/sel_bottom_right.png",path);
	style->sel_bottom_right=loadTexture(loadPath);
	if(!style->sel_bottom_right){
		rpg_freeGuiStyle(style);
		return NULL;
	}

	style->font=TTF_OpenFont(font_name,font_size);
	if(!style->font){
		fprintf(stderr,"Could not load font %s: %s\n",font_name,TTF_GetError());
		rpg_freeGuiStyle(style);
		return NULL;
	}
	style->textColor.r=0;
	style->textColor.g=0;
	style->textColor.b=0;

	style->bLeft=16;
	style->bRight=16;
	style->bTop=16;
	style->bBottom=16;

	style->selBLeft=7;
	style->selBRight=7;
	style->selBTop=7;
	style->selBBottom=7;

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
	if(style->sel_center){
		SDL_DestroyTexture(style->sel_center);
	}
	if(style->sel_left){
		SDL_DestroyTexture(style->sel_left);
	}
	if(style->sel_right){
		SDL_DestroyTexture(style->sel_right);
	}
	if(style->sel_top){
		SDL_DestroyTexture(style->sel_top);
	}
	if(style->sel_bottom){
		SDL_DestroyTexture(style->sel_bottom);
	}
	if(style->sel_top_left){
		SDL_DestroyTexture(style->sel_top_left);
	}
	if(style->sel_top_right){
		SDL_DestroyTexture(style->sel_top_right);
	}
	if(style->sel_bottom_left){
		SDL_DestroyTexture(style->sel_bottom_left);
	}
	if(style->sel_bottom_right){
		SDL_DestroyTexture(style->sel_bottom_right);
	}
	if(style->font){
		TTF_CloseFont(style->font);
	}
	free(style);
}
