#ifndef loadsave_h
#define loadsave_h
#include "../../shared/include/level.h"
#include <stdio.h>

// prototypes for starting up the level editor and closing the level editor - opening a file, loading a file, saving to a file, etc.

Mode getMode (void);
char * getFileName(void);
FILE * GetFile(void);
Level * LoadLevel(void);
void LoadLevelFromFile(Level *level, FILE *fp);
void SaveLevel(Level *level);
void DestroyLevel(Level *level);
void MallocTiles(Level *level);

#endif
