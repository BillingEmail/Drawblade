#include "include/editrun.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../shared/include/level.h"
#include "../shared/include/texture.h"

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
	editor->textureArray[LAVA][BLANK] = NULL;
	editor->textureArray[LAVA][BRICK] = Load_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/blue64x64.png");
	editor->textureArray[LAVA][PLAYER] = Load_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/green128x128.png");

	editor->backgroundArray[LAVA] = Load_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/bg1280x720.png");
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
	LevelType currentTheme = editor->level->theme;
	Texture_Render(editor->backgroundArray[theme], editor->container->renderer, 0, 0, NULL);
		
	for (int i = 0; i < editor->level.height; i++) {
		for (int j = 0; j < editor->level.width; j++) {
			Texture_Render(
			editor->textureArray[theme][editor->level->tileArray[i][j]]
			editor->renderer, j * 64, i * 64, editor->camera	
			);
		}
	}
	
	for (int i = 0; i <= editor->level.height; i++) {
		SDL_RenderDrawLine(editor->renderer,
		0 + editor->camera.x, i * 64 + editor->camera.y,
		editor->level.width * 64 + editor->camera.x, i * 64 + editor->camera.y);
	}
	for (int j = 0; j <= editor->level.width; i++) {
		SDL_RenderDrawLine(editor->renderer,
		i * 64 + editor->camera.x, 0 + editor->camera.y,
		i * 64 + editor->camera.x, editor->level.height * 64 + editor->camera.y);
	}
	
	Texture_Render(editor->textureArray[theme][editor->currentItem], editor->container->renderer,
	editor->container->mouse.x - 32, editor->container->mouse.y - 32, editor->camera);
}

void LevelEditor_Update(LevelEditor *editor) {
	Container_Refresh(editor->container);
	
	if (editor->container->keyboardstate[SDL_SCANCODE_Q]) break;
	
	LevelEditor_getCurrentTheme(editor);	
	LevelEditor_getCurrentItemType(editor);
	
	if (LevelEditor_checkEditTile(LevelEditor *editor)) {
			editor->level->tileArray
			[(editor->container->mouse.y + editor->container->camera.y) / 64]
			[(editor->container->mouse.x + editor->container->camera.x) / 64] =
 	        editor->currentItem;
	}

}

bool LevelEditor_checkEditTile(LevelEditor *editor) {
	int yclick = (editor->container->mouse.y + editor->container->camera.y) / 64;
	int xclick = (editor->container->mouse.x + editor->container->mouse.x) / 64;
	if (editor->container->mouse.leftClick) {
		if (yclick < editor->level.height && yclick >= 0 && xclick < editor->level.width && xclick >= 0) {
			return true;
		}
				
	}
	return false;
}
void LevelEditor_getCurrentItemType(LevelEditor *editor) {
	if (editor->container->keyboardstate[SDL_SCANCODE_1]) editor->currentItem = BLANK;
	if (editor->container->keyboardstate[SDL_SCANCODE_2]) editor->currentItem = BRICK;
	if (editor->container->keyboardstate[SDL_SCANCODE_3]) editor->currentItem = PLAYER;
}

void LevelEditor_getCurrentTheme(LevelEditor *editor) {
	if (editor->container->keyboardstate[SDL_SCANCODE_I]) editor->level->theme = MEDIEVAL;
	if (editor->container->keyboardstate[SDL_SCANCODE_O]) editor->level->theme = ICE;
	if (editor->container->keyboardstate[SDL_SCANCODE_P]) editor->level->theme = LAVA;
}
