//#include "../include/startscreen.h"
#include "../include/game.h"
#include "../../shared/include/container.h"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void) {
	Container *contianer;
	Game *game;

	container = New_Container(SCREEN_WIDTH, SCREEN_HEIGHT);
	game = New_Game(container);
	ShowStartScreen(container);

	Game_Run(game);

	Game_Close(game);	
	Container_Destroy(container);

	return 0;
}
