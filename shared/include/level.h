#ifndef level_h
#define level_h
#include <stdio.h>

/* Length of a side of a tile in pixels */
#define TILE_SCALE 64

// This is for what type of enemy is in what tile
typedef enum _EntityTypes {
	BLANK, BRICK, PLAYER, FLYING, MELEE, RANGED, BOSS
} Tile;
// This is for whether you are loading a file or not
typedef enum _Mode {
	NEW, LOAD, FAIL
} Mode;

// This is for what the type of the level is
typedef enum  _LevelType {
	MEDIEVAL, ICE, LAVA, SPOOKY
} LevelType;

//Definition of a level
typedef struct _Level {
	int height;
	int width;
	LevelType theme;
	Tile **tileArray;
} Level;


Mode getMode(void);
//functions for getting the file
char * getFileName(void);
FILE * GetFile(void);
//functions for level struct
Level * New_Level(void);
void Level_LoadFromFile(Level *level, FILE *fp);
void Level_Save(Level *level);
void Level_Destroy(Level *level);
void Level_CreateTiles(Level *level);
#endif
