#include "../../shared/include/level.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main (void) {
	Level * level = New_Level();
	
	level->tileArray[13][1] = BRICK;
	level->tileArray[12][1] = BRICK;
	level->tileArray[11][1] = BRICK;
	

	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 50; j++) {
			printf("%d ", level->tileArray[i][j]);
		}
		printf("\n");
	}

	SaveLevel(level);

	return 0;
}
