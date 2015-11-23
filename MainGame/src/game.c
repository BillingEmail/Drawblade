#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/world.h"
#include "../../shared/include/container.h"
#include "../include/player.h"

Game * New_Game(Container *container) {
	Game *ret;

	ret = malloc(sizeof(Game));

	/* load the player stuff */
	ret->player = New_Player(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(
					container->renderer, "../assets/img/Medieval/player.png"
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

//	ret->hud = Create_HUD(container);


	return ret;
}

/* Main game loop */
void Game_Run(Game *game, Container *container) {
	long long frame = 1;
	/* load the first level */
	game->world = LoadWorld(game->current_level, game->player, container);

	game->running = true;

	while (game->running) {
		/* Update the world */
		World_Update(game->world, game->player, frame);
		/* Render the world */
		World_Render(game->world, frame, container);
//		HUD_Render(game->hud, container->renderer);

		/* If the world has been completed */
		if (game->world->is_complete) {
			/* switch to next world -- will be a function later */
			game->current_level++;
			game->world = LoadWorld(game->current_level, game->player, container);
		}

		/* end game upon death */
		if (game->player->traits->hitpoints == 0) {
			/* Do better */
			//Game_RenderDeathScreen(game);
			/* restart world */
			World_Destroy(game->world);
			game->world = LoadWorld(game->current_level, game->player, container);
		}

		Container_Refresh(container);
		Container_PlayerUpdateCamera(container, game->player);
	}
}

/* Close and destroy everything */
void Game_Close(Game *game) {
//	Hud_Destroy(game->hud)
	World_Destroy(game->world);
	Destroy_Player(game->player);
	free(game);
}

World * LoadWorld(int worldnum, Player *p, Container *c) {
	World *ret;
	char path[64];

	strcpy(path, "../assets/levels/level");
	sprintf(path, "%d", worldnum);
	strcat(path, ".lvl");
	ret = NewWorld_FromFile(path, p, c);

	return ret;
}
