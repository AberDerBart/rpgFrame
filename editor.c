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
	SDL_RenderCopy(render,tileTextures[i],NULL,&rect);
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

void tilesMenu(){
redrawTilesMenu();
rpg_setGui(tilesGui);
}

void setTile(){
rpg_tile* tile;
int x,y;
x=rpg_protagonist->x;
y=rpg_protagonist->y;
tile=rpg_getMapTile(rpg_curScene->map,x,y,D_NONE);
rpg_loadTileTexture(tile,selectedTile,selectedLayer);
((Uint32*)layerSurfs[selectedLayer]->pixels)[x+10*y]=selectedTile;
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

	rpg_bindKey(SDLK_l,&layersMenu);
	rpg_bindKey(SDLK_s,&rpg_guiDown);
	rpg_bindKey(SDLK_w,&rpg_guiUp);
	rpg_bindKey(SDLK_RETURN,&rpg_guiSelect);
	rpg_bindKey(SDLK_t,&tilesMenu);

	rpg_bindKey(SDLK_a,&tilesLeft);
	rpg_bindKey(SDLK_d,&tilesRight);
	rpg_bindKey(SDLK_SPACE,&setTile);

	rpg_bindKey(SDLK_o,&save);

	if(argc==2){
		scene.map=rpg_parseMap(argv[1]);
		for(i=0;i<4;i++){
			sprintf(path,"layer%d.bmp",i);
			layerSurfs[i]=SDL_LoadBMP(path);
		}
		baseSurf=SDL_LoadBMP(path);
	}else{
		scene.map=rpg_createMap(10,10,3);
		for(i=0;i<4;i++){
			layerSurfs[i]=SDL_CreateRGBSurface(0,10,10,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
		}
		baseSurf=SDL_CreateRGBSurface(0,10,10,32,0x00ff0000,0x0000ff00,0x000000ff,0xff000000);
	}

	scene.chars=list_create();
	rpg_curScene=&scene;
	list_insert(scene.chars,rpg_createCharacter("img/sprites/crosshair.png"));
	//list_insert(scene.chars,rpg_createCharacter("img/sprites/char.png"));
	scene.focus=scene.chars->next->item;
	rpg_protagonist=scene.focus;

	rpg_mainloop();

	return 0;
}
