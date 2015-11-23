//#include "../include/startscreen.h"
#include "../include/game.h"
#include "../../shared/include/container.h"
#include "../include/mainmenu.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void) {
	Container *container;
	Game *game;
	MainMenu *StartScreen;

	container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	StartScreen = New_MainMenu(container);

	if (MainMenu_Show(StartScreen, container) == START) {
		game = New_Game(container);
		Game_Run(game, container);
		Game_Close(game);
	}

	Container_Destroy(container);

	return 0;
}
