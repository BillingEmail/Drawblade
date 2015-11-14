/* game.h - overhead shit */

#ifndef GAME_H
#define GAME_H

#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "world.h"
#include "character.h"


typedef struct __game_overhead {
	struct {
		CharacterType *type;
		int index; /* definitely 0 */
	} player;

	/* load them all on start and switch between or load them as we go?
	 * load them from the file that is, not loading the characters
	 * and objects etc -- this would really just be a 2d array of enums
	 * and not much else so it's not that big of a memory issue */
	 /* if we do load them all at once, then we must also have the index
	  * for the current level in the level array and not a pointer just
	  * to one
	  */
	Level *currentLevel;

	bool running;
	bool paused;

} Game;

#endif
