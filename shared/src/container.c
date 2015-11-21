#include "../include/container.h"

#ifdef GAME_H
#include "../../MainGame/include/player.h"
#endif

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>


/* 
   This is to set up the container, which holds all SDL Objects
   It first mallocs the container, then adds in each object one by one
   It needs the width and height the screen should be so it can make a window
   of that size
*/
Container * New_Container(int SCREEN_WIDTH, int SCREEN_HEIGHT) {
	Container * container = malloc(sizeof(Container));
	
	/* Initialize SDL */
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	/* Create the window */
	container->window = New_Window(SCREEN_WIDTH, SCREEN_HEIGHT);	
	/* Create the renderer for the window */
	container->renderer = New_Renderer(container->window);

	/* Create the camera */
	container->camera = malloc(sizeof(SDL_Rect));
	container->camera->w = SCREEN_WIDTH;
	container->camera->h = SCREEN_HEIGHT;
	container->camera->x = 0;
	container->camera->y = 0;

	/* Sets up the keyboard */
	container->keyboardstate = SDL_GetKeyboardState(NULL);
	
	return container;
}

/* Destroys the container and quits SDL */
void Container_Destroy(Container * container) {
	SDL_DestroyWindow(container->window);
	SDL_DestroyRenderer(container->renderer);
	free(container->camera);
	free(container);
	container = NULL;

	SDL_Quit();
	IMG_Quit();
}

/* 
   The refresh holds all of the SDL functions that need to be called
   every frame.  These include delaying each frame, getting keyboard input, etc.
*/
void Container_Refresh(Container * container) {
	/* Holds the return of SDL_GetMouseState() */
	uint32_t mouse_state;
	/* Refresh the screen */
	SDL_RenderPresent(container->renderer);
	SDL_Delay(16);
	/* Update they keyboardstate of the container */
	SDL_PumpEvents();

	/* Retrieve the mouse state -- X, Y, leftClick, rightClick */
	mouse_state = SDL_GetMouseState(&container->mouse.x, &container->mouse.y);
	/* true if left mouse button is clicked, otherwise false */
	container->mouse.leftClick = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);
	/* "       right "                                       */
	container->mouse.rightClick = mouse_state & SDL_BUTTON(SDL_BUTTON_RIGHT);

	/* Clear the screen before rendering the next frame */
	SDL_SetRenderDrawColor(container->renderer, 255, 255, 255, 255);
	SDL_RenderClear(container->renderer);
}

/* Create a window of size <width, height> */
SDL_Window * New_Window(int width, int height) {
	SDL_Window *ret = SDL_CreateWindow(
		"Drawblade", 
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

/* Makes the renderer for the window, allowing textures to be displayed */
SDL_Renderer * New_Renderer(SDL_Window *window) {
	SDL_Renderer *ret = SDL_CreateRenderer(
		window,
		/* Default to first available graphics driver */
		-1,
		/* Use hardware acceleration and render in sync with refresh rate */
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);
	
	if (!ret) {
		fprintf(stderr, "Could not create renderer");
		return NULL;
	}
	return ret;
}

/* Updates camera depending on arrow keys */
void Container_KeyBoardUpdateCamera(Container *container) {
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

#ifdef GAME_H
/* Updates camera depending on player's position */
void Container_PlayerUpdateCamera(Container *container, Player *p) {
	container->camera->x = p->object->dstrect.x - Camera->w / 2;
	container->camera->y = p->object->dstrect.y - Camera->h / 2;
}
#endif
