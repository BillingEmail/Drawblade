#include "../include/menu.h"
#include "../../shared/include/container.h"
#include "../include/game.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

int main(void) {
	Container *container;
	Menu *MainMenu;
	MenuReturn Selection;
	Game *game;

	container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	MainMenu = New_MainMenu(container);

	Selection = Menu_Run(MainMenu, container);
	switch(Selection.action) {
		case START:
			game = New_Game(container);
			Game_Run(game, container);
			Game_Close(game);
		break;
		default:;
	}

	Container_Destroy(container);

	return 0;
}
