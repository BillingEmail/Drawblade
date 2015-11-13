#ifndef level_h
#define level_h

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
#endif
