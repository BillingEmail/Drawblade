#include "../include/SDLhelpers.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


/* Makes the screen and checks if it is made correctly */
SDL_Window * MakeWindow(int width, int height) {
	SDL_Window *ret = SDL_CreateWindow(
	"LevelEditor", 
	SDL_WINDOWPOS_CENTERED, 
	SDL_WINDOWPOS_CENTERED, 
	width, 
	height, 
	SDL_WINDOW_SHOWN
	);

	if(!ret) {
		fprintf(stderr, "Could not create window\n");
		return NULL;
	}

	return ret;
}

SDL_Renderer * MakeRenderer(SDL_Window *window) {
	SDL_Renderer *ret = SDL_CreateRenderer(
	window,
	-1,
	SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);
	
	if (!ret) {
		fprintf(stderr, "Could not create renderer");
		return NULL;
	}
	return ret;
}
/* Updates camera depending on arrow keys */
void KeyBoardUpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState) {
	if (KeyboardState[SDL_SCANCODE_UP]) {
		Camera->y -= 5;
	}
	if (KeyboardState[SDL_SCANCODE_DOWN]) {
		Camera->y += 5;
	}
	if (KeyboardState[SDL_SCANCODE_RIGHT]) {
		Camera->x += 5;
	}
	if (KeyboardState[SDL_SCANCODE_LEFT]) {
		Camera->x -= 5;
	}

}
/* Updates camera depending on player's coordinates */
void PlayerUpdateCamera(SDL_Rect *Camera, CharacterType *ct, int instance_index) {
	Camera->x = ct->object_type->instances[instance_index].dstrect.x - Camera->w / 2;
	Camera->y = ct->object_type->instances[instance_index].dstrect.y - Camera->h / 2;
}
