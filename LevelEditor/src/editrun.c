#include "../include/editrun.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1280;
#define SCREEN_HEIGHT 720;


/* 
   All of the functions for editing the level are broken down this way
   The LevelEditor is made, then ran, and then when it is quit it is ended
*/
void Level_Edit(Level *level) {
	LevelEditor *editor = New_LevelEditor(level);
	LevelEditor_Run(editor);
	LevelEditor_End(editor);	
	
}

/* 
   Mallocs a LevelEditor object, sets up the container, and then 
   fills in the arrays of textures
*/
LevelEditor * New_LevelEditor(Level *level) {
	LevelEditor *editor = malloc(sizeof(LevelEditor));
	editor->container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	editor->level = level;
	editor->currentItem = BLANK;
	editor->textureArray[LAVA][BRICK] = Load_Texture(editor->container->renderer,
	 "lavabrick.png");
	editor->textureArray[LAVA][PLAYER] = Load_Texture(editor->container->renderer,
	 "lavaplayer.png");

	editor->backgroundArray[LAVA] = Load_Texture(editor->container->renderer,
	 "lavabackground.png");
}

/* Destroys the LevelEditor */
void LevelEditor_End(Leveleditor *editor) {
	Container_Destroy(editor->container);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++) {
			Destroy_Texture(editor->textureArray[i][j]);
		}
		Destroy_Texture(editor->backgroundArray[4]);
	}
	free(editor);
}
/* A loop that Renders and Updates the LevelEditor */
void LevelEditor_Run(LevelEditor *editor) {
	while(1) {
		LevelEditor_Render(editor);
		LevelEditor_Update(editor);
	}
}


void LevelEditor_Render(LevelEditor *editor) {

}

void LevelEditor_Update(LevelEditor *editor) {
	Container_Refresh(editor->container);
	
	if (editor->container->keyboardstate[SDL_SCANCODE_Q]) break;
	
	LevelEditor_getCurrentTheme(editor);	
	LevelEditor_getCurrentItemType(editor);

	if (editor->container->mouse.leftClick) {
		editor->level->tileArray
			[(editor->container->mouse.y + editor->container->camera.y) / 64]
			[(editor->container->mouse.x + editor->container->camera.x) / 64] =
 	        editor->currentItem;
	}	
}

void LevelEditor_getCurrentItemType(LevelEditor *editor) {
	if (editor->container->keyboardstate[SDL_SCANCODE_1]) editor->currentItem = BLANK;
	if (editor->container->keyboardstate[SDL_SCANCODE_2]) editor->currentItem = BRICK;
	if (editor->container->keyboardstate[SDL_SCANCODE_3]) editor->currentItem = PLAYER;
}

void LevelEditor_getCurrentTheme(LevelEditor *editor) {
	if (editor->container->keyboardstate[SDL_SCANCODE_U]) editor->level->theme = JUNGLE;
	if (editor->container->keyboardstate[SDL_SCANCODE_I]) editor->level->theme = LAVA;
}
