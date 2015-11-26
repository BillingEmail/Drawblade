#include <stdbool.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/button.h"
#include "../include/menu.h"

Menu * New_Menu(Texture *background) {
	Menu *ret;

	ret = malloc(sizeof(Menu));
	ret->background = background;

	ret->buttons = malloc(sizeof(Button *));
	ret->buttonCount = 0;
	ret->buttonsSize = 1;
	
	/*
	ret->textboxes = malloc(sizeof(Textbox *));
	ret->textboxCount = 0;
	ret->textboxSize = 1;
	ret->currentTextbox = 0;
	*/

	return ret;
}

void Menu_AddButton(Menu *m, Button *b) {
	if (m->buttonCount == m->buttonsSize) {
		m->buttons = realloc(m->buttons, m->buttonsSize * 2 * sizeof(Button *));
		m->buttonsSize *= 2;
	}
	m->buttons[m->buttonCount] = b;
	m->buttonCount++;
}

void Menu_Destroy(Menu *m) {
	for (int i = 0; i < m->buttonCount; i++) {
		Button_Destroy(m->buttons[i]);
	}
	Destroy_Texture(m->background);
	free(m);
}

MenuReturn Menu_Run(Menu *m, Container *container) {
	MenuReturn ret;
	bool running = true;
//	int SelectedTextbox = 0; /* Focused textbox */

	while (running) {
		Container_Refresh(container);
		for (int i = 0; i < m->buttonCount; i++) {
			if (Button_Clicked(m->buttons[i], container)) {
				ret.action = m->buttons[i]->action;
				ret.text = NULL;
//				ret.text = m->textboxes[SelectedTextbox]->text;
				running = false;
			}
		}
//		for (int i = 0; i < m->textboxCount; i++) {
//			if (TextBox_Clicked(m->textboxes[i], container)) {
//				SelectedTextbox = i;
//			}
//		}
		Texture_Render(m->background, container->renderer, 0, 0, NULL);
		for (int i = 0; i < m->buttonCount; i++) {
			Button_Render(m->buttons[i], container);
		}
	}

	return ret;
}

Menu * New_MainMenu(Container *container) {
	/* Create menu with background texture */
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/MainMenu/background.png"));

	/* Add start button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/start.png"),
			START,
			435, 200, 357, 132
		)
	);

	/* Add Load Custom Level button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/loadcustomlevel.png"),
			LOAD_CUSTOM_LEVEL,
			435, 350, 357, 132
		)
	);

	/* Add quit button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/quit.png"),
			QUIT,
			435, 500, 357, 132
		)
	);

	return ret;
}

Menu * New_LoadLevelMenu(Container *container) {
	/* Create menu with background texture */
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/LoadLevel/background.png"));

	/* Add back button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/back.png"),
			BACK,
			850, 480, 357, 132
		)
	);

	/* Add start button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/start.png"),
			START,
			850, 480 - 132 - 10, 357, 132
		)
	);

	return ret;
}

void RunMenuManager(Menu *MainMenu, Menu *LoadLevelMenu, Container *container) {
	/* Default to MainMenu */
	Menu *CurrentMenu = MainMenu;
	/* The input from the user through the menu */
	MenuReturn MenuInput;
	/* Whether the loop should be running */
	bool running = true;
	/* The actual game */
	Game *game;

	while (running) {
		/* Run the menu, get the input (button click) */
		MenuInput = Menu_Run(CurrentMenu, container);
		/* If we're on the main menu */
		if (CurrentMenu == MainMenu) {
			printf("Menu: MainMenu\n");
			switch(MenuInput.action) {
				/* If the start button was pressed */
				case START:
					puts("Action: START");
					/* Start the game - Adventure mode */
					game = New_Game(container, ADVENTURE, NULL);
					/* Run the game, going through level1, level2, etc */
					Game_Run(game, container);
					/* Clean up */
					Game_Close(game);
					/* Back to main menu */
					CurrentMenu = MainMenu;
				break;
				/* If the quit button was pressed */
				case QUIT:
					puts("Action: QUIT");
					/* Close */
					running = false;
				break;
				/* If the Load Custom Level button was pressed */
				case LOAD_CUSTOM_LEVEL:
					puts("Action: LOAD_CUSTOM_LEVEL");
					/* Switch to LoadLevelMenu */
					CurrentMenu = LoadLevelMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		/* If we're on the Load Level menu */
		} else if (CurrentMenu == LoadLevelMenu) {
			puts("Menu: LoadLevelMenu");
			switch (MenuInput.action) {
				/* If the start button was pressed */
				case START:
					/* Start the custom level *********************************/
					/* Start a new game in CUSTOM_LEVEL mode using the text */
					game = New_Game(container, CUSTOM_LEVEL, MenuInput.text);
					/* Run the game */
					Game_Run(game, container);
					/* After the game is finished, clean up */
					Game_Close(game);
					/* Go back to the MainMenu */
					CurrentMenu = MainMenu;
				break;
				/* If the back button was pressed */
				case BACK:
					/* Go back to the Main Menu */
					CurrentMenu = MainMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		} /* It the user typed something but clicked Back button */
		if (MenuInput.text) free(MenuInput.text);
	}
}
