#ifndef level_h
#define level_h
#include <stdio.h>
// This is for what type of enemy is in what tile
typedef enum _EntityTypes {
	BLANK, BRICK, PLAYER, ENEMY
} Tile;
// This is for whether you are loading a file or not
typedef enum _Mode {
	NEW, LOAD, FAIL
} Mode;

// This is for what the type of the level is
typedef enum  _LevelType {
	LAVA, WATER, MEDEIVAL, CITY
} LevelType;

//Definition of a level
typedef struct _Level {
	int height;
	int width;
	LevelType theme;
	Tile **tileArray;
} Level;

Mode getMode(void);
char * getFileName(void);
FILE * GetFile(void);
Level * New_Level(void);
void LoadLevelFromFile(Level *level, FILE *fp);
void SaveLevel(Level *level);
void DestroyLevel(Level *level);
void CreateTiles(Level *level);
#endif
