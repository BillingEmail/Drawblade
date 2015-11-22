#include "../include/leveleditor.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../shared/include/level.h"
#include "../../shared/include/texture.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TILE_SCALE 64

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
	editor->currentItem = BRICK;
	editor->container->camera->y = editor->level->height * TILE_SCALE - SCREEN_HEIGHT;
	editor->container->camera->x = 0;
	editor->textureArray[LAVA][BLANK] = NULL;
	
	editor->textureArray[LAVA][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Lava/brick.png");
	editor->textureArray[ICE][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Ice/brick.png");
	editor->textureArray[MEDIEVAL][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Medieval/brick.png");
	editor->textureArray[SPOOKY][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Spooky/brick.png");

	editor->textureArray[LAVA][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Lava/player.png");
	editor->textureArray[ICE][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Ice/player.png");
	editor->textureArray[MEDIEVAL][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Medieval/player.png");
	editor->textureArray[SPOOKY][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Spooky/player.png");
	
	editor->backgroundArray[LAVA] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Lava/background.png");
	editor->backgroundArray[ICE] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Ice/background.png");
	editor->backgroundArray[MEDIEVAL] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Medieval/background.png");
	editor->backgroundArray[SPOOKY] = New_Texture(editor->container->renderer,
	 "../assets/img/LevelEditor/Spooky/background.png");

	return editor;
}

/* Destroys the LevelEditor */
void LevelEditor_End(LevelEditor *editor) {
	Container_Destroy(editor->container);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++) {
			Destroy_Texture(editor->textureArray[i][j]);
	
		}
		Destroy_Texture(editor->backgroundArray[i]);
	}
	free(editor);
}
/* A loop that Renders and Updates the LevelEditor */
void LevelEditor_Run(LevelEditor *editor) {
	while(1) {
		if (editor->container->keyboardstate[SDL_SCANCODE_Q] &&
		    editor->container->keyboardstate[SDL_SCANCODE_LSHIFT]) break;
		LevelEditor_Render(editor);
		LevelEditor_Update(editor);
	}
}


void LevelEditor_Render(LevelEditor *editor) {
	LevelType theme = editor->level->theme;
	Texture_Render(editor->backgroundArray[theme], editor->container->renderer, 0, 0, NULL);
		
	for (int i = 0; i < editor->level->height; i++) {
		for (int j = 0; j < editor->level->width; j++) {
			Texture_Render(
			editor->textureArray[theme][editor->level->tileArray[i][j]],
			editor->container->renderer, j * TILE_SCALE, i * TILE_SCALE, editor->container->camera	
			);
		}
	}
	
	for (int i = 0; i <= editor->level->height; i++) {
		SDL_RenderDrawLine(editor->container->renderer,
		0 - editor->container->camera->x, i * TILE_SCALE - editor->container->camera->y,
		editor->level->width * TILE_SCALE - editor->container->camera->x, i * TILE_SCALE - editor->container->camera->y);
	}
	for (int i = 0; i <= editor->level->width; i++) {
		SDL_RenderDrawLine(editor->container->renderer,
		i * TILE_SCALE - editor->container->camera->x, 0 - editor->container->camera->y,
		i * TILE_SCALE - editor->container->camera->x, editor->level->height * TILE_SCALE - editor->container->camera->y);
	}
	
	Texture_Render(editor->textureArray[theme][editor->currentItem], editor->container->renderer,
	editor->container->mouse.x - 32, editor->container->mouse.y - 32, NULL);
}

void LevelEditor_Update(LevelEditor *editor) {
	Container_Refresh(editor->container);	
	Container_KeyBoardUpdateCamera(editor->container);
	LevelEditor_AssertCameraBounds(editor);
	LevelEditor_getCurrentTheme(editor);	
	LevelEditor_getCurrentItemType(editor);
	
	if (LevelEditor_checkEditTile(editor)) {
			editor->level->tileArray
			[(editor->container->mouse.y + editor->container->camera->y) / TILE_SCALE]
			[(editor->container->mouse.x + editor->container->camera->x) / TILE_SCALE] =
 	        editor->currentItem;
	}
}

void LevelEditor_AssertCameraBounds(LevelEditor *editor) {
	if (editor->container->camera->y < 0 - TILE_SCALE / 2)
	    editor->container->camera->y = 0 - TILE_SCALE / 2;
	
	if (editor->container->camera->y > editor->level->height * TILE_SCALE - SCREEN_HEIGHT + TILE_SCALE / 2)
	    editor->container->camera->y = editor->level->height * TILE_SCALE - SCREEN_HEIGHT + TILE_SCALE / 2;
	
	if (editor->container->camera->x < 0 - TILE_SCALE / 2) 
		editor->container->camera->x = 0 - TILE_SCALE / 2;

	if (editor->container->camera->x > editor->level->width * TILE_SCALE - SCREEN_WIDTH + TILE_SCALE / 2)
		editor->container->camera->x = editor->level->width * TILE_SCALE - SCREEN_WIDTH + TILE_SCALE / 2;
	
	if (SCREEN_WIDTH > editor->level->width * TILE_SCALE) {
		editor->container->camera->x = (SCREEN_WIDTH - editor->level->width * TILE_SCALE) / 2;
	}
	if (SCREEN_HEIGHT > editor->level->height * TILE_SCALE) {
		editor->container->camera->y = (SCREEN_HEIGHT - editor->level->height * TILE_SCALE) / 2;
	}
}

bool LevelEditor_checkEditTile(LevelEditor *editor) {
	int yclick = (editor->container->mouse.y + editor->container->camera->y) / TILE_SCALE;
	int xclick = (editor->container->mouse.x + editor->container->camera->x) / TILE_SCALE;
	if (editor->container->mouse.leftClick) {
		if (yclick < editor->level->height && yclick >= 0 && xclick < editor->level->width && xclick >= 0) {
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
	if (editor->container->keyboardstate[SDL_SCANCODE_U]) editor->level->theme = MEDIEVAL;
	if (editor->container->keyboardstate[SDL_SCANCODE_I]) editor->level->theme = ICE;
	if (editor->container->keyboardstate[SDL_SCANCODE_O]) editor->level->theme = LAVA;
	if (editor->container->keyboardstate[SDL_SCANCODE_P]) editor->level->theme = SPOOKY;
}
