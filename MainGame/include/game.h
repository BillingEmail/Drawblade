/* game.h - The running game (excludes level editors and menus
 *
 * Author: Sean Rapp
 */

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

	int current_level; /* Used in mode = ADVENTURE. Used to load the adventure
	                    * level for the game, i.e. assets/levels/level<current_level>.lvl */

	bool running; /* Totally necessary - if the should be running */
	bool paused; /* Game paused */

	GameMode mode; /* Mode for the game - either ADVENTURE or CUSTOM_LEVEL */
	
	char *custom_level_path; /* Unused if mode == ADVENTURE; used to load the
	                          * custom level in CUSTOM_LEVEL mode  */

	Texture *levelComplete; /* When you complete a level, this shows up. */
	Texture *levelFailed; /* Likewise when you fail. Do better. */

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
