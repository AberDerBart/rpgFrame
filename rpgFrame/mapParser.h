#ifndef MAPPARSER_H
#define MAPPARSER_H

#include "structs.h"
#include "map.h"

int rpg_setTiletable(char*);
rpg_map* rpg_parseMap(char*);
void rpg_freeTiletable();

#endif
