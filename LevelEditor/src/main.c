#include "../include/loadsave.h"
//#include <SDL/SDL2.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main (int argc, const char* argv[]) {
	Level * level = LoadLevel();
	level->tileArray[0][1] = ENEMY;
	SaveLevel(level);

	return 0;
}
