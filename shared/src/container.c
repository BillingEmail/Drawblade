#include "../include/SDLhelpers.h"
#include "../../MainGame/include/character.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


/* 
   This is to set up the container, which holds all SDL Objects
   It first mallocs the container, then adds in each object one by one
   It needs the width and height the screen should be so it can make a window
   of that size
*/
SDLContainer * New_Container(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	Container * container = malloc(sizeof(Container));
	
	//Uses the New_Window function to make the screen
	container->window = New_Window(SCREEN_WIDTH, SCREEN_HEIGHT);
	
	//Adjusts the position of the camera
	container->camera = malloc(sizeof(SDL_Rect));
	container->camera->w = SCREEN_WIDTH;
	container->camera->h = SCREEN_HEIGHT;
	container->camera->x = 0;
	container->camera->y = 0;

	//Uses the New_Renderer function to make the renderer
	container->renderer = New_Renderer(container->window);
	//Sets up the keyboard
	container->keyboardstate = SDL_GetKeyboardState(NULL);
	
	//Initializes important SDL functions
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	return container;
}
/* Destroys the components of the container and frees the pointers */
void Container_Destroy(Container * container) {
	SDL_DestroyWindow(container->window);
	SDL_DestroyRenderer(container->renderer);
	free(container->camera);
	free(container);
	SDL_Quit();
	IMG_Quit();
}

/* 
   The refresh holds all of the SDL functions that need to be called
   every frame.  These include delaying each frame, getting keyboard input, etc.
*/
void Container_Refresh(Container * container) {
	uint32_t mouse_state;
	SDL_RenderPresent(container->renderer);
	SDL_Delay(16);
	SDL_PumpEvents();

	mouse_state = SDL_GetMouseState(&container->mouse,x, &container->mouse.y);
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		container->mouse.leftClick = true;
	} else {
		container->mouse.leftClick = false;
	}
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		container->mouse.rightClick = true;
	} else {
		container->mouse.rightClick = false;
	}

	SDL_SetRenderDrawColor(container->renderer, 255, 255, 255, 255);
	SDL_RenderClear(container->renderer);
}

/* Makes the screen and checks if it is made correctly */
SDL_Window * New_Window(int width, int height) {
	SDL_Window *ret = SDL_CreateWindow(
	"The Window", 
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
SDL_Renderer * New_Renderer(SDL_Window *window) {
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
void KeyBoardUpdateCamera(Container *container) {
	if (container->keyboardstate[SDL_SCANCODE_UP]) {
		container->camera->y -= 5;
	}
	if (container->keyboardstate[SDL_SCANCODE_DOWN]) {
		container->camera->y += 5;
	}
	if (container->keyboardState[SDL_SCANCODE_RIGHT]) {
		container->camera->x += 5;
	}
	if (container->keyboardstate[SDL_SCANCODE_LEFT]) {
		container->camera->x -= 5;
	}

}

/* Updates camera depending on player's coordinates */
void PlayerUpdateCamera(Container *container, CharacterType *ct, int instance_index) {
	container->camera->x = ct->object_type->instances[instance_index].dstrect.x - Camera->w / 2;
	container->camera->y = ct->object_type->instances[instance_index].dstrect.y - Camera->h / 2;
}


