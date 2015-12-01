#include "../include/leveleditor.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../shared/include/level.h"
#include "../../shared/include/texture.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720


/* 
   All of the functions for editing the level are broken down this way
   The LevelEditor is made, then ran, and then when it is quit it is ended
*/
void Level_Edit(Level *level, Container *container) {
	LevelEditor *editor = New_LevelEditor(level, container);
	LevelEditor_Run(editor);
	LevelEditor_End(editor);	
	
}

/* 
   Mallocs a LevelEditor object, sets up the container, and then 
   fills in the arrays of textures
*/
LevelEditor * New_LevelEditor(Level *level, Container *container) {
	LevelEditor *editor = malloc(sizeof(LevelEditor));
	/* Sets up all of the defaults for the level editor */
	editor->container = container;
	editor->level = level;
	editor->currentItem = BRICK;
	editor->container->camera->y = editor->level->height * TILE_SCALE - SCREEN_HEIGHT;
	editor->container->camera->x = 0;
	for (int i = 0; i < 3; i++) {
		editor->FirstBkgRP[i].x = 0;
		editor->FirstBkgRP[i].y = 0;
	}
/* 
The next section loads all of the textures needed for the level 
editor into the textureArray and backgroundArray 
*/
	//Sets up the eraser icon for if the currently selected option is erase
	editor->blankIcon = New_Texture(editor->container->renderer,"../assets/img/LevelEditor/eraser.png");
	
	//Sets up all of the blank spaces just to make sure they are null
	editor->textureArray[LAVA][BLANK] = NULL;
	editor->textureArray[ICE][BLANK] = NULL;
	editor->textureArray[MEDIEVAL][BLANK] = NULL;
	editor->textureArray[SPOOKY][BLANK] = NULL;
	
	//Sets up the Bricks 
	editor->textureArray[LAVA][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/Lava/brick.png");
	editor->textureArray[ICE][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/Ice/brick.png");
	editor->textureArray[MEDIEVAL][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/Medieval/brick.png");
	editor->textureArray[SPOOKY][BRICK] = New_Texture(editor->container->renderer,
	 "../assets/img/Spooky/brick.png");

	//Sets up the Players
	editor->textureArray[LAVA][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Lava/player.png");
	editor->textureArray[ICE][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Ice/player.png");
	editor->textureArray[MEDIEVAL][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Medieval/player.png");
	editor->textureArray[SPOOKY][PLAYER] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Spooky/player.png");
	
	//Sets up the Flying Enemies
	editor->textureArray[LAVA][FLYING] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Lava/flying_enemy.png");
	editor->textureArray[ICE][FLYING] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Ice/flying_enemy.png");
	editor->textureArray[MEDIEVAL][FLYING] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Medieval/flying_enemy.png");
	editor->textureArray[SPOOKY][FLYING] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Spooky/flying_enemy.png");
	
	//Sets up the Melee Enemies
	editor->textureArray[LAVA][MELEE] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Lava/melee_enemy.png");
	editor->textureArray[ICE][MELEE] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Ice/melee_enemy.png");
	editor->textureArray[MEDIEVAL][MELEE] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Medieval/melee_enemy.png");
	editor->textureArray[SPOOKY][MELEE] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Spooky/melee_enemy.png");
	
	//Sets up the Ranged Enemies
	editor->textureArray[LAVA][RANGED] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Lava/ranged_enemy.png");
	editor->textureArray[ICE][RANGED] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Ice/ranged_enemy.png");
	editor->textureArray[MEDIEVAL][RANGED] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Medieval/ranged_enemy.png");
	editor->textureArray[SPOOKY][RANGED] = New_Texture(editor->container->renderer,
	"../assets/img/LevelEditor/Spooky/ranged_enemy.png");

	//Sets up the Boss Enemies
	editor->textureArray[LAVA][GOALPOST] = New_Texture(editor->container->renderer,
	"../assets/img/goalpost.png");
	editor->textureArray[ICE][GOALPOST] = New_Texture(editor->container->renderer,
	"../assets/img/goalpost.png");
	editor->textureArray[MEDIEVAL][GOALPOST] = New_Texture(editor->container->renderer,
	"../assets/img/goalpost.png");
	editor->textureArray[SPOOKY][GOALPOST] = New_Texture(editor->container->renderer,
	"../assets/img/goalpost.png");
	
	//Sets up the Backgrounds


	editor->backgroundArray[MEDIEVAL][0] = New_Texture(editor->container->renderer,
	 "../assets/img/Medieval/background_still.png");
	editor->backgroundArray[SPOOKY][0] = New_Texture(editor->container->renderer,
	 "../assets/img/Spooky/background_still.png");
	editor->backgroundArray[LAVA][0] = New_Texture(editor->container->renderer,
	"../assets/img/Lava/background_tiled.png");
	editor->backgroundArray[ICE][0] = New_Texture(editor->container->renderer,
	"../assets/img/Ice/background_tiled.png");

	
	return editor;
}

/* Destroys the LevelEditor */
void LevelEditor_End(LevelEditor *editor) {
	
	//destroys the eraser
	Destroy_Texture(editor->blankIcon);
	
	//loops through the two arrays and destroys all of the textures
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			Destroy_Texture(editor->textureArray[i][j]);
	
		}
		for (int j = 0; j < 1; j++) {
			Destroy_Texture(editor->backgroundArray[i][j]);
		}
	}
	
	//frees the editor
	free(editor);
}
/* A loop that Renders and Updates the LevelEditor */
void LevelEditor_Run(LevelEditor *editor) {
	while(1) {
		//The case for breaking out of the loop is holding shift and q
		if (editor->container->keyboardstate[SDL_SCANCODE_Q] &&
		    editor->container->keyboardstate[SDL_SCANCODE_LSHIFT]) break;

		//the render and update
		LevelEditor_Render(editor);
		LevelEditor_Update(editor);
	}
}

/* This renders all of the components of the level editor */
void LevelEditor_Render(LevelEditor *editor) {
	/*
	Sets a shortcut for finding the theme of the level
	The theme is needed because everything that is rendered
	is based on the current theme
	*/
	LevelType theme = editor->level->theme;
	
	//This renders the background for the editor
/*	Texture_Render(editor->backgroundArray[theme][1], editor->container->renderer, 0, 0, NULL);
	Texture_Render(editor->backgroundArray[theme][0], editor->container->renderer, editor->FirstBkgRP[0].x, editor->FirstBkgRP[0].y, NULL);
	Texture_Render(editor->backgroundArray[theme][0], editor->container->renderer, editor->FirstBkgRP[1].x, editor->FirstBkgRP[1].y, NULL);
	Texture_Render(editor->backgroundArray[theme][0], editor->container->renderer, editor->FirstBkgRP[2].x, editor->FirstBkgRP[2].y, NULL);
*/
	Texture_Render(editor->backgroundArray[theme][0], editor->container->renderer, 0, 0, NULL);
	/* 
	This loops through the level in the editor and renders each of the objects in the level
	It basically goes through each tile of the level, and if there is an object, then 
	Renders that tile into screen space
	*/
	for (int i = 0; i < editor->level->height; i++) {
		for (int j = 0; j < editor->level->width; j++) {
			if (editor->level->tileArray[i][j] == BLANK) continue;
			if (editor->level->tileArray[i][j] == BRICK) {
				Texture_RenderBrick(
					editor->textureArray[theme][editor->level->tileArray[i][j]], 
					editor->container->renderer, j * TILE_SCALE, i * TILE_SCALE, editor->container->camera,
					Level_GetBrickChoice(editor->level, j, i)
				);	
			}
			else {
				Texture_Render(
					editor->textureArray[theme][editor->level->tileArray[i][j]],
					editor->container->renderer, j * TILE_SCALE, i * TILE_SCALE, editor->container->camera	
				);
			}
		}
	}
	
	/* 
	These two loops go through and make lines that make up the grid for the level editor 
	SDL_RenderDrawLine draws a line when given its two endpoints.  The for loops basically
	make lines for each height that is as long as the width, and vice versa
	*/
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
	
	//Renders the currently selected item on the mouse cursor location, so the user can see it
	if (editor->currentItem != BRICK && editor->currentItem != BLANK) {
		Texture_Render(editor->textureArray[theme][editor->currentItem], editor->container->renderer,
			editor->container->mouse.x - TILE_SCALE / 2, editor->container->mouse.y - TILE_SCALE / 2, NULL);
	}

	//If the currently selected item is BLANK, it renders the eraser icon
	if (editor->currentItem == BLANK) {
		Texture_Render(editor->blankIcon, editor->container->renderer, 
		editor->container->mouse.x - 78 / 2, editor->container->mouse.y - 72 / 2, NULL);
	}

	if (editor->currentItem == BRICK) {
		Texture_RenderBrick(
			editor->textureArray[theme][BRICK],
			editor->container->renderer, 
			editor->container->mouse.x - TILE_SCALE / 2, 
			editor->container->mouse.y - TILE_SCALE / 2, 
			NULL,	
			ALL
		);
	}

}

void Texture_RenderBrick(Texture *t, SDL_Renderer *r, int x, int y, SDL_Rect *Camera, BrickChoice b) {
	if (t == NULL) {
		return;
	}
	
	SDL_Rect renderRect;
	SDL_Rect srcRect = { b * 32, 0, 32, 32 };

	if(Camera) {
		renderRect.x = x - Camera->x;
		renderRect.y = y - Camera->y;
	} else {
		renderRect.x = x;
		renderRect.y = y;
	}

	renderRect.w = TILE_SCALE;
	renderRect.h = TILE_SCALE;
	SDL_RenderCopy(r, t->texture, &srcRect, &renderRect);
}
/* This updates all of the components of the editor, including the container components */
void LevelEditor_Update(LevelEditor *editor) {
	//Refreshes the container
	Container_Refresh(editor->container);	

	/*
	The first function moves the camera based on keyboard input, 
	the second makes sure the camera is in the bounds 
	*/
	Container_KeyBoardUpdateCamera(editor->container);
	LevelEditor_AssertCameraBounds(editor);
	
	//These two uses the keyboard in the editor and adjusts the theme and itemtype based on keyboardinput
	LevelEditor_getCurrentTheme(editor);	
	LevelEditor_getCurrentItemType(editor);

	//This takes the mouse and sees if the user has clicked in a valid location
	if (LevelEditor_checkEditTile(editor)) {
			//This sets the place they have clicked in to the currentItem
			editor->level->tileArray
				[(editor->container->mouse.y + editor->container->camera->y) / TILE_SCALE]
				[(editor->container->mouse.x + editor->container->camera->x) / TILE_SCALE] =
 		        editor->currentItem;
	}
	
	LevelEditor_AdjustBackground(editor, editor->container->camera->x - editor->container->lastcp.x, 
	editor->container->camera->y - editor->container->lastcp.y);

	editor->container->lastcp.x = editor->container->camera->x;
	editor->container->lastcp.y = editor->container->camera->y;
}

void LevelEditor_AdjustBackground(LevelEditor *editor, int xdiff, int ydiff) {
	xdiff = (int)(xdiff * .20);
	ydiff = (int)(ydiff * .20);
	
		editor->FirstBkgRP[1].x -= xdiff;

		editor->FirstBkgRP[0].x = -editor->backgroundArray[editor->level->theme][0]->w + 1;
		editor->FirstBkgRP[2].x = editor->backgroundArray[editor->level->theme][0]->w - 1;
		
}

/* 
This sets the bounds for where the camera can go for the editor
The bounds are basically the size of the level, but there is a buffer of half of a tile on all sides, 
So that the user can easily tell that it is the end of the level
*/
void LevelEditor_AssertCameraBounds(LevelEditor *editor) {
	//Upper bounder
	if (editor->container->camera->y < 0 - TILE_SCALE / 2)
	    editor->container->camera->y = 0 - TILE_SCALE / 2;
	//Lower bounder
	if (editor->container->camera->y > editor->level->height * TILE_SCALE - SCREEN_HEIGHT + TILE_SCALE / 2)
	    editor->container->camera->y = editor->level->height * TILE_SCALE - SCREEN_HEIGHT + TILE_SCALE / 2;
	//Left bounder
	if (editor->container->camera->x < 0 - TILE_SCALE / 2) 
		editor->container->camera->x = 0 - TILE_SCALE / 2;
	//Right bounder
	if (editor->container->camera->x > editor->level->width * TILE_SCALE - SCREEN_WIDTH + TILE_SCALE / 2)
		editor->container->camera->x = editor->level->width * TILE_SCALE - SCREEN_WIDTH + TILE_SCALE / 2;
	
	/* 
	The next two statements are for the edge case where the level is smaller than the screen
	They basically center the tile array instead of allowing the user to move it and asserting bounds
	They are last in fthe function because they have to take priority if they should be used over
	the other camera adjustments
	*/

	//bounds the x axis
	if (SCREEN_WIDTH > editor->level->width * TILE_SCALE) {
		editor->container->camera->x = - (SCREEN_WIDTH / 2) + TILE_SCALE * editor->level->width / 2;
	}

	//bounds the y axis
	if (SCREEN_HEIGHT > editor->level->height * TILE_SCALE) {
		editor->container->camera->y = - (SCREEN_HEIGHT / 2) + TILE_SCALE * editor->level->height / 2;
	}
}

/*
This is basically to check whether or not a click occurred, and then whether or not the click was within
the bounds of the tile array.  If it is not, it returns false, and the click is not registered on the array
*/
bool LevelEditor_checkEditTile(LevelEditor *editor) {
	//shortcuts for the x and y coordinates of the mouse
	int yclick = (editor->container->mouse.y + editor->container->camera->y) / TILE_SCALE;
	int xclick = (editor->container->mouse.x + editor->container->camera->x) / TILE_SCALE;
	
	//checks for left click
	if (editor->container->mouse.leftClick) {
		//checks if the click is within the bounds of the tileArray
		if (yclick < editor->level->height && yclick >= 0 && xclick < editor->level->width && xclick >= 0) {
			return true;
		}
				
	}
	return false;
}

/* Collects keyboard inputs for the current item type */
void LevelEditor_getCurrentItemType(LevelEditor *editor) {
	if (editor->container->keyboardstate[SDL_SCANCODE_1]) editor->currentItem = BLANK;
	if (editor->container->keyboardstate[SDL_SCANCODE_2]) editor->currentItem = BRICK;
	if (editor->container->keyboardstate[SDL_SCANCODE_3]) editor->currentItem = PLAYER;
	if (editor->container->keyboardstate[SDL_SCANCODE_4]) editor->currentItem = GOALPOST;
/*	if (editor->container->keyboardstate[SDL_SCANCODE_5]) editor->currentItem = MELEE;
	if (editor->container->keyboardstate[SDL_SCANCODE_6]) editor->currentItem = RANGED;
	if (editor->container->keyboardstate[SDL_SCANCODE_7]) editor->currentItem = BOSS;
*/
}

/* Collects keyboard inputs for the current theme */
void LevelEditor_getCurrentTheme(LevelEditor *editor) {
	if (editor->container->keyboardstate[SDL_SCANCODE_U]) editor->level->theme = MEDIEVAL;
	if (editor->container->keyboardstate[SDL_SCANCODE_I]) editor->level->theme = ICE;
	if (editor->container->keyboardstate[SDL_SCANCODE_O]) editor->level->theme = LAVA;
	if (editor->container->keyboardstate[SDL_SCANCODE_P]) editor->level->theme = SPOOKY;
}
