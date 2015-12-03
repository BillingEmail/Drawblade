/* game.h - overhead shit */

#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "world.h"
#include "../../shared/include/container.h"
#include "HUD.h"

/* The structure of a game */

//Needed in the New_Game function
typedef enum { ADVENTURE, CUSTOM_LEVEL } GameMode;

/* The struct for a game */
typedef struct __game_overhead {
	World *world; /* the current world */
	HUD *hud; /* the ui the player can use */

	int current_level; 

	bool running; /* set to false when the player dies, level is complete, etc. */
	bool paused; /* stops the game */

	GameMode mode; /*lets you know whether game mode is adventure or not */
	
	char *custom_level_path; /* Unused if mode == ADVENTURE */

	Texture *levelComplete; /* Textures for the end screens */
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
