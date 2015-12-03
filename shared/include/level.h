/* level.h - The blueprint for a world.
 * Used in loading/saving levels, and editing
 * them.
 *
 * Author: Satya Patel
 */


#ifndef level_h
#define level_h
#include <stdio.h>

/* Length of a side of a tile in pixels */
#define TILE_SCALE 32

// This is for what type of enemy is in what tile
typedef enum _EntityTypes {
	BLANK, BRICK, PLAYER, FLYING, MELEE, RANGED, GOALPOST
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


typedef enum _BrickChoice {
	NUDE, TOP, RIGHT, BOTTOM, LEFT,
	TOPRIGHT, RIGHTBOTTOM, BOTTOMLEFT, TOPLEFT,
	TOPRIGHTLEFT, TOPRIGHTBOTTOM, RIGHTBOTTOMLEFT, TOPBOTTOMLEFT,
	TOPBOTTOM, RIGHTLEFT, ALL
} BrickChoice;

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

/* because satya didn't think when designing */
Level * New_LevelFromFile(const char *path);

/* convenicneniceencnce */
Level * New_LevelByName(const char *name);

/* because satya has bad design */
Level * New_BlankLevel(int width, int height);

/* " */
void Level_SaveByName(Level *level, const char *name);

BrickChoice Level_GetBrickChoice(Level *level, int x, int y);
#endif
