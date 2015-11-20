#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/world.h"
#include "../../shared/container.h"

Game * New_Game(Containter *container) {
	Game *ret;

	ret = malloc(sizeof(Game));

	/* load the player stuff */
	ret->player = New_Player(
		New_Object(
			New_Spritesheet(
				New_Texture(
					container->renderer, "../../assets/img/player.png"
				),
				4, /* Number of animations */
				4, 4, 4, 4 /* Number of sprites in each animation */
			),
			16, 32 /* width and height of player */
		),
		0, 0 /* initial x and y of player, to be changed when the world is loaded */
	);

	/* assign some stuff */
	ret->current_level = 1;
	ret->running = false;
	ret->paused = false;

	ret->hud = Create_HUD(container);


	return ret;
}

/* Main game loop */
void Game_Run(Game *game, Container *container) {
	long long frame = 1;
	/* load the first level */
	game->world = LoadWorld(game->current_level);

	game->running = true;

	while (game->running) {
		/* Update the world */
		World_Update(game->world, game->player);
		/* Render the world */
		World_Render(game->world, frame, container->renderer, container->camera);
		Hud_Render(game->hud, container->renderer);

		/* If the world has been completed */
		if (game->world->is_complete) {
			/* switch to next world -- will be a function later */
			game->current_level++;
			game->world = LoadWorld(game->current_level);
		}

		/* end game upon death */
		if (game->player->traits->is_dead) {
			/* Do better */
			Game_RenderDeathScreen(game);
			/* restart world */
			World_Destroy(game->world);
			game->world = LoadWorld(game->current_level);
		}

		Container_Refresh(container);
		Container_PlayerUpdateCamera(container, game->player);
	}
}

/* Close and destroy everything */
void Game_Close(Game *game) {
	World_Destroy(game->world);
	Destroy_Player(game->player);
	free(game);
}

World * LoadWorld(int worldnum) {
	World *ret;
	char path[64];
	ret = NewWorldFromFile


}
