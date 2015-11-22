/* game.h - overhead shit */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "world.h"
#include "player.h"
#include "../../shared/include/container.h"
#include "HUD.h"

typedef struct __game_overhead {
	Player *player; /* the player */
	World *world; /* the current world */
	HUD *hud;

	int current_level; /* ok */

	bool running; /* idk */
	bool paused; /* ok */

} Game;

/* I don't know */
Game * New_Game(Container *container);

/* run the god damn fucking game */
void Game_Run(Game *game);

/* done */
void Game_Close(Game *game);

/* Load level 1, 2, 3, w/e */
void LoadWorld(int worldnum);

#endif
