#include "../include/editrun.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#define SCREEN_WIDTH 1280;
#define SCREEN_HEIGHT 720;

void Level_Edit(Level *level) {
	LevelEditor *editor = New_LevelEditor(level);
	LevelEditor_Run(editor);
	LevelEditor_End(editor);	
	
}

LevelEditor * New_LevelEditor(Level *level) {
	LevelEditor *editor = malloc(sizeof(LevelEditor));
	editor->container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	editor->level = level;
	
	editor->textureArray[LAVA][BRICK] = Load_Texture(editor->container->renderer,
	 "lavabrick.png");
	editor->textureArray[LAVA][PLAYER] = Load_Texture(editor->container->renderer,
	 "lavaplayer.png");

	editor->backgroundArray[LAVA] = Load_Texture(editor->container->renderer,
	 "lavabackground.png");
}

void LevelEditor_Edit(LevelEditor *editor) {
	while(1) {

		if(editor->container->keyboardstate[SDL_SCANCODE_Q]) {
			break;
		}
		
		


	}

}
