#include "../include/SDLhelpers.h"
#include "../../MainGame/include/character.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

SDLWrapper * New_Wrapper(int width, int height) {
	SDLWrapper * wrapper = malloc(sizeof(SDLWrapper));
	wrapper->window = MakeWindow(width, height);
	wrapper->camera = malloc(sizeof(SDL_Rect));
	wrapper->camera->w = width;
	wrapper->camera->h = height;
	wrapper->camera->x = 0;
	wrapper->camera->y = 0;
	wrapper->renderer = MakeRenderer(wrapper->window);
	wrapper->keyboardstate = SDL_GetKeyboardState(NULL);
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	return wrapper;
}

void SDLWrapper_Destroy(SDLWrapper * wrapper) {
	SDL_DestroyWindow(wrapper->window);
	SDL_DestroyRenderer(wrapper->renderer);
	free(wrapper->camera);
	free(wrapper);
	SDL_Quit();
	IMG_Quit();
}


void SDLWrapper_Refresh(SDLWrapper * wrapper) {
	SDL_RenderPresent(wrapper->renderer);
	SDL_Delay(16);
	SDL_PumpEvents();
	SDL_SetRenderDrawColor(wrapper->renderer, 255, 255, 255, 255);
	SDL_RenderClear(wrapper->renderer);
}

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

/* Makes a renderer */
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


