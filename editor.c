#include "rpgFrame/all.h"

int selectedLayer;

void selectLayer0(){
selectedLayer=0;
rpg_setGui(NULL);
}

void selectLayer1(){
selectedLayer=1;
rpg_setGui(NULL);
}

void selectLayer2(){
selectedLayer=2;
rpg_setGui(NULL);
}

void selectLayer3(){
selectedLayer=3;
rpg_setGui(NULL);
}

void selectLayerBase(){
rpg_setGui(NULL);
}

rpg_action layers[]={{&selectLayer0,"Layer 0"},{&selectLayer1,"Layer 1"},{&selectLayer2,"Layer 2"},{&selectLayer3,"Layer 3"},{&selectLayerBase,"Base"}};
rpg_gui* layersGui;
rpg_gui* tilesGui;
int selectedTile;
SDL_Texture* tilesGuiTexture;
SDL_Surface* layerSurfs[3];
SDL_Surface* baseSurf;

void layersMenu(){
rpg_setGui(layersGui);
}

void drawTilesMenu(){
	int i;
	SDL_Rect rect;

	rect.w=32;
	rect.h=32;

	tilesGuiTexture=tilesGui->texture;

	SDL_SetRenderTarget(render,tilesGuiTexture);

	for(i=0;i<=tileTypes;i++){
		rect.x=(i%8)*32;
		rect.y=(i/8)*32;
		if(tileTextures[i]){
			SDL_RenderCopy(render,tileTextures[i]->texture[0],NULL,&rect);
		}
	}


	SDL_SetRenderTarget(render,NULL);

	tilesGui->texture=NULL;
	rpg_redrawGui(tilesGui);
}

void redrawTilesMenu(){
	int i;
	SDL_Rect rect;

	rect.w=32;
	rect.h=32;

	SDL_SetRenderTarget(render,tilesGui->texture);

	SDL_RenderCopy(render,tilesGuiTexture,NULL,NULL);
	rect.x=(selectedTile%8)*32;
	rect.y=(selectedTile/8)*32;
	SDL_RenderDrawRect(render,&rect);
	SDL_SetRenderTarget(render,NULL);
}

void tilesRight(){
if(currentGui==tilesGui){
	selectedTile++;
	if(selectedTile>tileTypes){
		selectedTile=0;
	}
	redrawTilesMenu();
}
}

void tilesLeft(){
	if(currentGui==tilesGui){
		selectedTile--;
		if(selectedTile<0){
			selectedTile=tileTypes;
		}
		redrawTilesMenu();
	}
}	

void tilesDown(){
	if(currentGui==tilesGui){
		selectedTile+=8;
		if(selectedTile>tileTypes){
			selectedTile=0;
		}
		redrawTilesMenu();
	}
}

void tilesUp(){
	if(currentGui==tilesGui){
		selectedTile-=8;
		if(selectedTile<0){
			selectedTile=tileTypes;
		}
		redrawTilesMenu();
	}
}

void tilesMenu(){
	redrawTilesMenu();
	rpg_setGui(tilesGui);
}

void setTile(){
	rpg_tile* tile;
	int x,y;
	int w;

	w=rpg_curScene->map->width;

	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	tile=rpg_getMapTile(rpg_curScene->map,x,y,D_NONE);
	rpg_loadTileTexture(tile,selectedTile,selectedLayer);
	tile->rot[selectedLayer]=0;
	((Uint32*)layerSurfs[selectedLayer]->pixels)[x+w*y]=selectedTile|0xff000000;
}

void rotTile(){
	rpg_tile* tile;
	int x,y;
	int w;
	int rot;

	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	w=rpg_curScene->map->width;

	tile=rpg_getMapTile(rpg_curScene->map,x,y,D_NONE);

	rot=(tile->rot[selectedLayer]+1)%4;
	printf("rot: %x\n",(rot << 22) & 0x00c00000);

	tile->rot[selectedLayer]=rot;
	((Uint32*)layerSurfs[selectedLayer]->pixels)[x+w*y]&=0xff3fffff;
	((Uint32*)layerSurfs[selectedLayer]->pixels)[x+w*y]|=(rot << 22);
	printf("%x\n",((Uint32*)layerSurfs[selectedLayer]->pixels)[x+w*y]);
}

void toggleCollision(){
	int x,y,w;

	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	w=rpg_curScene->map->width;
	((Uint32*)baseSurf->pixels)[x+w*y]^=0x00010000;
	printf("%x\n",((Uint32*)baseSurf->pixels)[x+w*y]);
}

void nextEvent(){
	int x,y,w;
	Uint32 event;
	Uint32 collision;

	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	w=rpg_curScene->map->width;

	event=((Uint32*)baseSurf->pixels)[x+w*y] & 0x0000ffff;
	collision=((Uint32*)baseSurf->pixels)[x+w*y] & 0x00ff0000;
	event++;
	printf("Event: %d\n",event);
	((Uint32*)baseSurf->pixels)[x+w*y]=event|collision|0xff000000;

}

void prevEvent(){
	int x,y,w;
	Uint32 event;
	Uint32 collision;

	x=rpg_protagonist->x;
	y=rpg_protagonist->y;
	w=rpg_curScene->map->width;

	event=((Uint32*)baseSurf->pixels)[x+w*y] & 0x0000ffff;
	collision=((Uint32*)baseSurf->pixels)[x+w*y] & 0x00ff0000;
	event--;
	printf("Event: %d\n",event);
	((Uint32*)baseSurf->pixels)[x+w*y]=event|collision|0xff000000;
}

void save(){
	int i;
	char path[256];
	for(i=0;i<4;i++){
		sprintf(path,"layer%d.bmp",i);
		SDL_SaveBMP(layerSurfs[i],path);
	}
	SDL_SaveBMP(baseSurf,"base.bmp");
	printf("saved.\n");
}

int main(int argc,char** argv){
	int x,y;
	rpg_scene scene;
	SDL_Rect rect;
	rpg_tile tile;
	int i;
	char path[256];

	rpg_init();
	rpg_setTiletable("tiles.txt");

	tile.textures=malloc(sizeof(SDL_Texture*)*4);

	for(i=1;i<=tileTypes;i++){
		rpg_loadTileTexture(&tile,i,1);
	}

	guiStyle=rpg_loadGuiStyle("img/gui",STRETCH,"/usr/share/fonts/truetype/freefont/FreeSerif.ttf",22);
	
	rect.x=20;
	rect.y=20;
	rect.w=100;
	rect.h=250;

	layersGui=rpg_createChoiceGui(guiStyle,layers,rect,5);

	rect.x=364;
	rect.y=20;
	rect.w=256;
	rect.h=440;

	tilesGui=rpg_createBasicGui(guiStyle,rect);
	drawTilesMenu();
	redrawTilesMenu();

	rpg_setGui(tilesGui);

	rpg_bindKey(SDLK_s,&tilesDown);
	rpg_bindKey(SDLK_w,&tilesUp);
	rpg_bindKey(SDLK_a,&tilesLeft);
	rpg_bindKey(SDLK_d,&tilesRight);
	rpg_bindKey(SDLK_SPACE,&setTile);
	rpg_bindKey(SDLK_r,&rotTile);
	rpg_bindKey(SDLK_c,&toggleCollision);
	rpg_bindKey(SDLK_q,&prevEvent);
	rpg_bindKey(SDLK_e,&nextEvent);

	rpg_bindKey(SDLK_l,&layersMenu);
	rpg_bindKey(SDLK_s,&rpg_guiDown);
	rpg_bindKey(SDLK_w,&rpg_guiUp);
	rpg_bindKey(SDLK_RETURN,&rpg_guiSelect);
	rpg_bindKey(SDLK_t,&tilesMenu);

	rpg_bindKey(SDLK_o,&save);

	if(argc==2){
		scene.map=rpg_parseMap(argv[1]);
		for(y=0;y<scene.map->height;y++){
			for(x=0;x<scene.map->width;x++){
				scene.map->tiles[x+scene.map->width*y].collision=0;
			}
		}
		for(i=0;i<4;i++){
			sprintf(path,"%s/layer%d.bmp",argv[1],i);
			//layerSurfs[i]=SDL_LoadBMP(path);
			layerSurfs[i]=IMG_Load(path);
			if(layerSurfs[i]==NULL){
				printf("layer%d\n",i);
			}
		}
		//baseSurf=SDL_LoadBMP(path);
		sprintf(path,"%s/base.bmp",argv[1]);
		baseSurf=IMG_Load(path);
	}else{
		scene.map=rpg_createMap(10,10,3);
		for(i=0;i<4;i++){
			layerSurfs[i]=SDL_CreateRGBSurface(0,10,10,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
		}
		baseSurf=SDL_CreateRGBSurface(0,10,10,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
	}

	scene.map->chars=list_create();
	rpg_curScene=&scene;
	list_insert(scene.map->chars,rpg_createCharacter("img/sprites/crosshair.png"));
	//list_insert(scene.map->chars,rpg_createCharacter("img/sprites/char.png"));
	scene.focus=scene.map->chars->next->item;
	rpg_protagonist=scene.focus;

	rpg_mainloop();

	return 0;
}
