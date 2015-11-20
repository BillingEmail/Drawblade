#ifndef editrun_h
#define editrun_h

#include "../../shared/include/level.h"

typedef struct _LevelEditor {
	Container *container;
	Level *level;
	Texture textureArray[4][16];
	Texture backgroundArray[4];
} LevelEditor;

void Level_Edit(Level *level);
void LevelEditor *New_LevelEditor(Level *level);
void LevelEditor_Run(LevelEditor *editor);
void LevelEditor_End(LevelEditor *editor);


#endif
