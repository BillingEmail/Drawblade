#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include "../../include/behavior.h"
#include "../../include/character.h"
#include "../../include/object.h"
#include "../../../shared/include/spritesheet.h"
#include "../../../shared/include/texture.h"
#include "../../../shared/include/SDLhelpers.h"
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480


int main(void) {
	SDLWrapper * wrapper = New_Wrapper(SCREEN_WIDTH, SCREEN_HEIGHT);
	long long frame = 1;
	bool running = true;
	
	ObjectType *brickType;
	CharacterType *playerType;

	/* Create a new type of object - the brick */
	brickType = New_ObjectType(
		New_Spritesheet(
			New_Texture(
				wrapper->renderer,
				"../../../assets/img/brick32.png"
			),
			1,
			20
		),
		true,
		32,
		32
	);

	/* Create a new type of character - the player */
	playerType = New_CharacterType(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(
					wrapper->renderer,
					"../../../assets/img/player.png"
				),
				2,
				11, 11
			),
			true,
			28,
			40
		),
		NULL
	);

	/* Create a line of 20 bricks from (0, 480-64) to (1280, 480-64) */
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < 20; i++) { /*   x              y */
			ObjectType_AddObject(brickType, (31 * i), k * (31) + (480 - 32), 0, i % 20 + (2 * k));
		}
	}

	/* Create 3 bricks in a row with a space of 128 in between each */
	for (int i = 0; i < 3; i++) {
		ObjectType_AddObject(brickType, 256 + (64 * i), 480 - 128, 0, 0);
	}
	/* Create a brick 256 above the middle brick of the row of 3 */
	ObjectType_AddObject(brickType, 256 + 64, 480 - 256, 0, 0);


	CharacterType_AddCharacter(playerType, 64, 480 - 64 - 40, 0, 0);

//	background = New_Texture(renderer, "../../../assets/img/sky.png");

	while (running) {
		PlayerUpdateCamera(wrapper->camera, playerType, 0);
		CharacterType_MoveCharacter(playerType, 0, wrapper->keyboardstate);
		CharacterType_UpdateCharacter(playerType, 0, frame);
		if (wrapper->keyboardstate[SDL_SCANCODE_Q]) {
			running = false;
		}

		/* Render the background */
//		Texture_Render(background, renderer, 0, 0, wrapper->camera);

		/* Render the object */
		for (int i = 0; i < ObjectType_Count(brickType); i++) {
			ObjectType_RenderObject(brickType, wrapper->renderer, i, wrapper->camera);
		}

		CharacterType_RenderCharacter(playerType, wrapper->renderer, 0, wrapper->camera);

		if (frame % 10 == 0) {
			for (int i = 0; i < ObjectType_Count(brickType); i++) {
				ObjectType_ObjectNextSprite(brickType, i);
			}
		}

		frame++;
	}

//	Destroy_Texture(background);
	Destroy_ObjectType(brickType);
	Destroy_CharacterType(playerType);

	SDLWrapper_Destroy(wrapper);

	return 0;
}

