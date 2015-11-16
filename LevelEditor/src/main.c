#include "../include/loadsave.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main (void) {
	Level * level = LoadLevel();
	runLevelEditor(level);
	SaveLevel(level);

	return 0;
}
