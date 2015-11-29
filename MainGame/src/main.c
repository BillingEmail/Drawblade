#include <stdbool.h>
#include "../include/game.h"
#include "../../shared/include/container.h"
#include "../include/menu.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void) {
	/* Holds window, renderer, camera, etc */
	Container *container;

	/* Create the container */
	container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);

	/* Menu switcher, entire overheard, etc */
	RunMenuManager(container);

	/* Destroy everything in the container */
	Container_Destroy(container);

	return 0;
}
