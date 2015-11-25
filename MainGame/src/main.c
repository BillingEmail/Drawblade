#include "../include/menu.h"
#include "../include/container.h"
#include "../include/game.h"

#define SCREEN_WIDTH  1280
#define SCREEN_HEIGHT 720

int main(void) {
	Container *container;
	Menu *MainMenu;
	Game *game;

	container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	MainMenu = New_MainMenu(container);

	switch(Menu_Run(MainMenu, container)) {
		case START:
			game = New_Game(container);
			Game_Run(game, container);
			Game_Close(container);
		break;
		default;
	}

	Container_Destroy(container);

	return 0;
}
