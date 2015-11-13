#ifndef loadsave_h
#define loadsave_h
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
	Tile **tileArray;
} Level;

// prototypes for starting up the level editor and closing the level editor - opening a file, loading a file, saving to a file, etc.

Mode getMode (void);
char * getFileName(void);
FILE * GetFile(void);
Level * LoadLevel(void);
void LoadLevelFromFile(Level *level, FILE *fp);
void SaveLevel(Level *level);
void DestroyLevel(Level *level);
void MallocTiles(Level *level);

// prototypes for actual level editor - placing an object, deleting an object, moving an object, selecting the currently selected object, etc



#endif
