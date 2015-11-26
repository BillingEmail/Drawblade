#include <stdbool.h>
#include "../include/game.h"
#include "../../shared/include/container.h"
#include "../include/menu.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void) {
	/* Holds window, renderer, camera, etc */
	Container *container;
	/* Main Menu, Load Custom Level Menu */
	Menu *MainMenu;
	Menu *LoadLevelMenu;

	/* Create the container */
	container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	/* Load the menus */
	MainMenu = New_MainMenu(container);
	LoadLevelMenu = New_LoadLevelMenu(container);

	/* Menu switcher, entire overheard, etc */
	RunMenuManager(MainMenu, LoadLevelMenu, container);

	Menu_Destroy(MainMenu);
	Menu_Destroy(LoadLevelMenu);
	Container_Destroy(container);

	return 0;
}
