#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "../object.h"
#include "../spritesheet.h"
#include "../texture.h"

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

SDL_Window * MakeWindow(int w, int h);
SDL_Renderer * MakeRenderer(SDL_Window *window);
void UpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState);


int main(void) {
	SDL_Window *window;
	SDL_Renderer *renderer;
	Texture *background;

	SDL_Rect Camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	int frame = 1;
	bool running = true;

	ObjectType *brickType;

	const uint8_t *KeyboardState = SDL_GetKeyboardState(NULL);

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = MakeWindow(SCREEN_WIDTH, SCREEN_HEIGHT);
	renderer = MakeRenderer(window);

	/* Create a new type of object - the brick */
	brickType = New_ObjectType(
		New_Spritesheet(
			New_Texture(
				renderer,
				"src/img/brick.png"
			),
			1,
			20
		),
		true,
		64,
		64
	);

	/* Create a line of 20 bricks from (0, 480-64) to (1280, 480-64) */
	for (int i = 0; i < 20; i++) { /*   x              y */
		ObjectType_AddObject(brickType, (64 * i), 480 - 64, 0, 0);
	}
	/* Create 3 bricks in a row with a space of 128 in between each */
	for (int i = 0; i < 3; i++) {
		ObjectType_AddObject(brickType, 256 + (128 * i), 480 - 256, 0, 0);
	}
	/* Create a brick 256 above the middle brick of the row of 3 */
	ObjectType_AddObject(brickType, 256 + 128, 480 - 512, 0, 0);


	background = New_Texture(renderer, "src/img/sky.png");

	while (running) {
		UpdateCamera(&Camera, KeyboardState);

		if (KeyboardState[SDL_SCANCODE_Q]) {
			running = false;
		}

		/* Clear the screen */
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		/* Render the background */
		Texture_Render(background, renderer, 0, 0, &Camera);

		/* Render the object */
		for (int i = 0; i < ObjectType_Count(brickType); i++) {
			ObjectType_RenderObject(brickType, renderer, i, &Camera);
		}


		if (frame % 10 == 0) {
			for (int i = 0; i < ObjectType_Count(brickType); i++) {
				ObjectType_ObjectNextSprite(brickType, i);
			}
		}

		SDL_RenderPresent(renderer);

		SDL_Delay(16);
		SDL_PumpEvents();
		frame++;
	}

	Destroy_Texture(background);
	Destroy_ObjectType(brickType);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	IMG_Quit();

	return 0;
}

SDL_Window * MakeWindow(int w, int h) {
	SDL_Window *ret = SDL_CreateWindow(
		"Platformer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
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

void UpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState) {
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
