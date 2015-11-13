#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

SDL_Window * MakeWindow(void);
SDL_Renderer * MakeRenderer(SDL_Window *window);

int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Rect screen = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	bool running = true;

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = MakeWindow();
	renderer = MakeRenderer(window);


    FILE *fp;

    fp = OpenFile();

    uint8_t *keyboard = SDL_GetKeyboardState(NULL);


	while (running) {
        SDL_PumpEvents();
        if (keyboard[SDL_SCANCODE_Q]) {
            running = false;
        }

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);


		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	IMG_Quit();

	return 0;
}

SDL_Window * MakeWindow(void) {
	SDL_Window *ret = SDL_CreateWindow(
		"Platformer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN
	);

	if (!ret) {
		fprintf(stderr, "Could not create window\n");
		return NULL;
	}
	return ret;
}

SDL_Renderer * MakeRenderer(SDL_Window *window) {
	SDL_Renderer *ret = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);

	if (!ret) {
		fprintf(stderr, "Could not create renderer");
		return NULL;
	}
	return ret;
}

FILE * OpenFile(void) {


}
