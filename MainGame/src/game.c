#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/world.h"
#include "../../shared/include/container.h"
#include "../include/player.h"
#include "../include/game.h"
#include <SDL2/SDL.h>

Game * New_Game(Container *container) {
	Game *ret;

	ret = malloc(sizeof(Game));


	/* assign some stuff */
	ret->current_level = 1;
	ret->running = false;
	ret->paused = false;

	ret->hud = Create_HUD(container);


	return ret;
}

/* Main game loop */
void Game_Run(Game *game, Container *container) {
	unsigned int dt;
	unsigned int currentTime;
	unsigned int lastTime = 0;

	/* load the first level */
	game->world = LoadWorld(game->current_level, container);
	Container_PlayerUpdateCamera(container, game->world->player);

	game->running = true;
	/* **************** Main game loop ***************** */
	while (game->running) {
		currentTime = SDL_GetTicks();
		dt = currentTime - lastTime;
		lastTime = currentTime;
		/* *************** Run the world *************** */
		/* Update the world */
		World_Update(game->world, dt, container);


		/* Render the world */
		World_Render(game->world, dt, container);
		HUD_Render(game->hud, game->world->player, game->world->theme, container);


		/* ************** Switch to next level ********* */
		/* If the world has been completed */
		if (game->world->is_complete || container->keyboardstate[SDL_SCANCODE_N]) {
			/* switch to next world -- will later be a function with a transition */
//			game->current_level++;
			game->current_level = (game->current_level % 2) + 1;
			World_Destroy(game->world);
			game->world = LoadWorld(game->current_level, container);
		}


		/* HITPOINTS TEST ****************************************************/
		if (container->keyboardstate[SDL_SCANCODE_H]) {
			game->world->player->traits->hitpoints -= 0.5;
		}

		/* ************** Restart world on death ******* */
		if (game->world->player->traits->hitpoints == 0) {
			/* Do better */
			//Game_RenderDeathScreen(game);
			/* restart world */
			World_Destroy(game->world);
			game->world = LoadWorld(game->current_level, container);
		}

		/* ************* Quit game on keypress Q ****** */
		if (container->keyboardstate[SDL_SCANCODE_Q]) {
			game->running = false;
		}

		/* ************ Update the screen and camera ** */
		Container_Refresh(container);
		Container_PlayerUpdateCamera(container, game->world->player);
	}
}

/* Close and destroy everything */
void Game_Close(Game *game) {
//	Hud_Destroy(game->hud)
	World_Destroy(game->world);
	free(game);
}

World * LoadWorld(int worldnum, Container *c) {
	World *ret;
	char path[64];

	/* Path to level to be loaded */
	sprintf(path, "../assets/levels/level%d.lvl", worldnum);

	printf("LOADING LEVEL FROM: \"%s\"\n", path);
	ret = NewWorld_FromFile(path, c);

	return ret;
}
