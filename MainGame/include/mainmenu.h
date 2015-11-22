#ifndef mainmenu_H
#define mainmenu_H
#include "../../shared/include/container.h"
#include "../../shared/include/texture.h"
typedef enum {START, QUIT} Action;

/* A button on the menu */
typedef struct _button {
	Texture *texture;
	SDL_Rect renderRect;
	Action action;
} Button;

/* The main menu */
typedef struct _main_menu {
	Texture *background;
	struct {
		Button start;
		Button quit;
	} buttons;
} MainMenu;

/* Create a new main menu */
MainMenu * New_MainMenu(Container *container);

/* Destroy the main menu */
void MainMenu_Destroy(MainMenu *m);

/* Display the main menu and return the action selected */
Action MainMenu_Show(MainMenu *menu, Container *container);


/* EVERYTHING IS AN OBJECT
 * EVERYTHING
 */
#endif
