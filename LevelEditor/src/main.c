#include "include/loadsave.h"
#include "include/editrun.h"
#include <SDL/SDL2.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main (int argc, const char* argv[]) {
	Level * level = LoadLevel();
	runLevelEditor(level);
	SaveLevel(level);

	return 0;
}
