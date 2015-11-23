#include "../../include/mainmenu.h"
#include "../../../shared/include/container.h"
#include <stdio.h>

int main(void) {
	MainMenu *StartScreen;
	Container *container;

	container = New_Container(1280, 720);
	StartScreen = New_MainMenu(container);

	if (MainMenu_Show(StartScreen, container) == START) {
		puts("START");
	} else {
		puts("QUIT");
	}

	MainMenu_Destroy(StartScreen);
	Container_Destroy(container);

	return 0;
}	
