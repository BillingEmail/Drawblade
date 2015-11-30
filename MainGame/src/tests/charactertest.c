#include "../../include/character.h"
#include "../../../shared/include/container.h"
#include <SDL2/SDL.h>

int main(void) {
	Container *container = New_Container(720, 480);
	unsigned int dt;
	unsigned int currenttime, lasttime = 0;

	CharacterType *TestType = New_CharacterType(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(container->renderer, "../assets/img/Ice/melee_enemy.png"),
				10,
				8, 8, 4, 4, 3, 3, 2, 2, 1, 1
			),
			31, 33
		), NULL, 1, 100, 5
	);

	CharacterType_AddCharacter(TestType, 720 / 2, 480 / 2);
	CharacterType_AddCharacter(TestType, 720 / 3, 480 / 2);

	while (1) {
		currenttime = SDL_GetTicks();
		dt = currenttime - lasttime;
		lasttime = currenttime;
		Container_Refresh(container);
		for (int i = 0; i < TestType->character_traits_count; i++) {
			CharacterType_RenderCharacter(TestType, i, dt, container);
			CharacterType_UpdateCharacter(TestType, i, dt);
		}
		if (container->keyboardstate[SDL_SCANCODE_Q]) break;
	}


	Destroy_CharacterType(TestType);
	Container_Destroy(container);
	return 0;
}
