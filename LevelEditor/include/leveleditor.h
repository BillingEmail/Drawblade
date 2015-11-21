#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include "../../shared/include/level.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"
#include <stdbool.h>

typedef struct _LevelEditor {
	Container *container;
	Level *level;
	Texture *textureArray[4][16];
	Texture *backgroundArray[4];
	Tile currentItem;

} LevelEditor;

/*
  All of the functions for editing a level are within this
  It is broken into making a new leveleditor, running it,
  and destroying it
*/
void Level_Edit(Level *level);

LevelEditor *New_LevelEditor(Level *level);
void LevelEditor_End(LevelEditor *editor);

/* This has functions for rendering and updating a level */
void LevelEditor_Run(LevelEditor *editor);

void LevelEditor_Render(LevelEditor *editor);
void LevelEditor_Update(LevelEditor *editor);

/* This is a component of Update that will set the current tile type */
bool LevelEditor_checkEditTile(LevelEditor *editor);
void LevelEditor_getCurrentTheme(LevelEditor *editor);
void LevelEditor_getCurrentItemType(LevelEditor *editor);

#endif
