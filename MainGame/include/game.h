/* game.h - overhead shit */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "world.h"
#include "../../shared/include/container.h"
#include "HUD.h"

typedef enum { ADVENTURE, CUSTOM_LEVEL } GameMode;

typedef struct __game_overhead {
	World *world; /* the current world */
	HUD *hud;

	int current_level; /* ok */

	bool running; /* idk */
	bool paused; /* ok */

	GameMode mode;
	
	char *custom_level_path; /* Unused if mode == ADVENTURE */

	Texture *levelComplete;
	Texture *levelFailed;

} Game;

/* Make game, using mode ADVENTURE ore CUSTOM_LEVEL, if the latter,
 * the custom_level_path level is loaded and ran, custom_level_path is
 * ignored (should be NULL) if mode == ADVENTURE
 * this could just be checking if custom_level_path is NULL and assuming
 * adventure mode, but that relies on the MenuReturn working perfectly */
Game * New_Game(Container *container, GameMode mode, const char *custom_level_path);

/* run game */
void Game_Run(Game *game, Container *container);

/* done */
void Game_Close(Game *game);

/* Load level 1, 2, 3, w/e */
World * LoadWorld(int worldnum, Container *c);

#endif
