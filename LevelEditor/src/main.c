#include "../../shared/include/level.h"
#include "../include/leveleditor.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../../shared/include/container.h"
/* 
The main for the Level Editor
It calls the functions for Creating a level,
Saving a level, and Editing a level


thanks for that wonderful comment satya lol
 */
int main (void) {
	Level * level = New_Level();
	Container *container = New_Container(1280, 720);
	Level_Edit(level, container);
	Level_Save(level);

	return 0;
}
