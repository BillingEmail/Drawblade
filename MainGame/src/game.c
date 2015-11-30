#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/world.h"
#include "../../shared/include/container.h"
#include "../include/player.h"
#include "../include/game.h"
#include <SDL2/SDL.h>

/* Used to render either "Level Complete!" or "Level Failed" when
 * goalpost is touched or timer runs out, respectively */
void RenderLevelEnd(Container *container, Texture *t, World *world, unsigned int ct) {
	unsigned int dt, lastTime, currentTime, timeLeft;
	lastTime = 0;
	timeLeft = 3000;

	while (timeLeft > 0) {
		debug_msg("time left: %u\n", timeLeft);
		currentTime = SDL_GetTicks() - ct;
		dt = currentTime - lastTime;
		lastTime = currentTime;
		timeLeft -= dt;
		if (timeLeft < 16) {
			timeLeft = 0;
		}

		World_Render(world, 0, container);
		Texture_Render(t, container->renderer, 1280 / 2 - t->w / 2,
			720 / 2 - t->h / 2, NULL);
	
		Container_Refresh(container);
	}
}


Game * New_Game(Container *container, GameMode mode, const char *custom_level_name) {
	Game *ret;
	FILE *CustomLevelExists;
	/* Create the game overhead */
	ret = malloc(sizeof(Game));

	/* Copy the mode of the game */
	ret->mode = mode;

	/* Set up for Custom Level mode */
	if (mode == CUSTOM_LEVEL) {
		/* Place to store custom level path */
		ret->custom_level_path = malloc(64);
		/* If no name provided */
		if (!custom_level_name) {
			fprintf(stderr, "New_Game called with mode CUSTOM_LEVEL but no path provided\n");
		}
		puts(custom_level_name);
		/* Fill in the path to the custom level */
		sprintf(ret->custom_level_path, "../assets/levels/%s.lvl", custom_level_name);
		/* Test if level exists ***** */
		CustomLevelExists = fopen(ret->custom_level_path, "rb");
		/* If level exists found */
		if (CustomLevelExists) {
			fclose(CustomLevelExists);
		/* If level is not found */
		} else {
			/* Do not load game, return NULL */
			free(ret->custom_level_path);
			free(ret);
			return NULL;
		
		}
	}

	/* Initialize */
	ret->current_level = 1;
	ret->running = false;
	ret->paused = false;

	/* load the HUD */
	ret->hud = Create_HUD(container);

	ret->levelComplete = New_Texture(container->renderer, "../assets/img/levelcomplete.png");
	ret->levelFailed = New_Texture(container->renderer, "../assets/img/levelfailed.png");
	return ret;
}

/* Main game loop */
void Game_Run(Game *game, Container *container) {
	unsigned int dt;
	unsigned int currentTime;
	unsigned int lastTime = 0;



	/* load the first level */
	if (game->mode == ADVENTURE) {
		game->world = LoadWorld(game->current_level, container);
	} else if (game->mode == CUSTOM_LEVEL) {
		game->world = NewWorld_FromFile(game->custom_level_path, container);
	}
	Container_PlayerUpdateCamera(container, game->world->player);

	game->running = true;
	/* **************** Main game loop ***************** */
	while (game->running) {
		currentTime = SDL_GetTicks();
		dt = currentTime - lastTime;
		lastTime = currentTime;

		/* Health acting as a timer: finish the level in time */
		game->world->player->traits->hitpoints -= dt;
		if ((game->world->player->traits->hitpoints -= dt) < 0) {
			game->world->player->traits->hitpoints = 0;
		}

		/* *************** Run the world *************** */
		/* Update the world */
		World_Update(game->world, dt, container);


		/* Render the world */
		World_Render(game->world, dt, container);
		HUD_Render(game->hud, game->world->player, game->world->theme, container);


		/* ************** Switch to next level ********* */
		/* If the world has been completed */
		if (game->world->is_complete || container->keyboardstate[SDL_SCANCODE_N]) {
			RenderLevelEnd(container, game->levelComplete, game->world, currentTime);
			/* switch to next world -- TODO will later be a function with a transition */
			/* Increment world if ADVENTURE mode */			
			if (game->mode == ADVENTURE) {
				game->current_level++;
				World_Destroy(game->world);
				game->world = LoadWorld(game->current_level, container);
			/* Restart world if CUSTOM_LEVEL mode */
			} else if (game->mode == CUSTOM_LEVEL) {
				World_Destroy(game->world);
				game->world = NewWorld_FromFile(game->custom_level_path, container);
			}
		}


		/* HITPOINTS TEST ****************************************************/
		if (container->keyboardstate[SDL_SCANCODE_H]) {
			game->world->player->traits->hitpoints -= 0.5;
		}

		/* ************** Restart world on death ******* */
		/* TODO put in a function */
		if (game->world->player->traits->hitpoints == 0) {
			RenderLevelEnd(container, game->levelFailed, game->world, currentTime);
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
	HUD_Destroy(game->hud);
	World_Destroy(game->world);
	if (game->mode == CUSTOM_LEVEL) {
		free(game->custom_level_path);
	}
	free(game);
}

/* Load an Adventure mode level using the level number */
World * LoadWorld(int worldnum, Container *c) {
	World *ret;
	char path[64];

	/* Path to level to be loaded */
	sprintf(path, "../assets/levels/level%d.lvl", worldnum);

	printf("LOADING LEVEL FROM: \"%s\"\n", path);
	ret = NewWorld_FromFile(path, c);

	return ret;
}
