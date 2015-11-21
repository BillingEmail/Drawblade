#include "../../shared/include/level.h"
#include "../include/leveleditor.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main (void) {
	Level * level = New_Level();
	Level_Edit(level);
	SaveLevel(level);

	return 0;
}
