/* game.h - overhead shit */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "world.h"
#include "../../shared/include/container.h"
//#include "HUD.h"

typedef struct __game_overhead {
	World *world; /* the current world */
//	HUD *hud;

	int current_level; /* ok */

	bool running; /* idk */
	bool paused; /* ok */

} Game;

/* Make game */
Game * New_Game(Container *container);

/* run game */
void Game_Run(Game *game, Container *container);

/* done */
void Game_Close(Game *game);

/* Load level 1, 2, 3, w/e */
World * LoadWorld(int worldnum, Container *c);

#endif
