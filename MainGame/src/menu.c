#include <stdbool.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/button.h"
#include "../include/textbox.h"
#include "../include/menu.h"

/* Create a new Menu with a background */
Menu * New_Menu(Texture *background) {
	Menu *ret;

	ret = malloc(sizeof(Menu));
	ret->background = background;

	/* Create the list of buttons */
	ret->buttons = malloc(sizeof(Button *));
	ret->buttonCount = 0;
	ret->buttonsSize = 1;
	
	/* Create the list of textboxes */
	ret->textboxes = malloc(sizeof(Textbox *));
	ret->textboxCount = 0;
	ret->textboxesSize = 1;

	return ret;
}

/* Add a button to a menu */
void Menu_AddButton(Menu *m, Button *b) {
	/* Resize buttons array if cap is reached, increase cap accordingly */
	if (m->buttonCount == m->buttonsSize) {
		m->buttons = realloc(m->buttons, m->buttonsSize * 2 * sizeof(Button *));
		m->buttonsSize *= 2;
	}
	/* Add the button */
	m->buttons[m->buttonCount] = b;
	m->buttonCount++;
}

/* Add a textbox to a menu */
void Menu_AddTextbox(Menu *m, Textbox *t) {
	/* Resize buttons array if cap is reached, increase cap accordingly */
	if (m->textboxCount == m->textboxesSize) {
		m->textboxes = realloc(m->textboxes, m->textboxesSize * 2 * sizeof(Textbox *));
		m->textboxesSize *= 2;
	}
	/* Add the button */
	m->textboxes[m->textboxCount] = t;
	m->textboxCount++;
}

/* Destroy a menu from existence, all of its buttons and textboxes included */
void Menu_Destroy(Menu *m) {
	for (int i = 0; i < m->buttonCount; i++) {
		Button_Destroy(m->buttons[i]);
	}
	for (int i = 0; i < m->textboxCount; i++) {
		Textbox_Destroy(m->textboxes[i]);
	}
	Destroy_Texture(m->background);
	free(m);
}

/* Run a menu until a button is pressed, return the action of the
 * button and the text in a textbox, if any */
MenuReturn Menu_Run(Menu *m, Container *container) {
	MenuReturn ret;
	bool running = true;
	int SelectedTextbox = 0; /* Focused textbox */

	/* Clear keyboard inputs (prevents textbox buffer from overlowing from
	 * game inputs)
	 * Essentially, when the game was ran, all of the d's and
	 * a's etc were collected onto the event queue, and then
	 * when the game was quit and the menus ran again, the
	 * textbox on the load custom level menu would collect all of the inputs on
	 * the queue, which may have been more than it could store, causing a
	 * segfault -- this line fixes that by dumping all those d's and a's */
	SDL_FlushEvent(SDL_TEXTINPUT);

	while (running) {
		Container_Refresh(container);
		/* If a button is clicked, set the return and exit loop */
		for (int i = 0; i < m->buttonCount; i++) {
			if (Button_Clicked(m->buttons[i], container)) {
				ret.action = m->buttons[i]->action;
				ret.text = m->textboxes[SelectedTextbox]->text;
				running = false;
			}
		}

		/* If a textbox is clicked, set the focus to it */
		for (int i = 0; i < m->textboxCount; i++) {
			if (Textbox_Clicked(m->textboxes[i], container)) {
				SelectedTextbox = i;
			}
		}

		if (m->textboxCount > 0) {		
			/* Listen for input in the focused textbox */
			Textbox_ReadInput(m->textboxes[SelectedTextbox]);
		}

		/* Render the components */
		Texture_Render(m->background, container->renderer, 0, 0, NULL);
		for (int i = 0; i < m->buttonCount; i++) {
			Button_Render(m->buttons[i], container);
		}
		for (int i = 0; i < m->textboxCount; i++) {
			Textbox_Render(m->textboxes[i], container);
		}
	}

	return ret;
}


/* ******************************** Shortcut to make the main menu */
Menu * New_MainMenu(Container *container) {
	/* Create menu with background texture */
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/MainMenu/background.png"));

	/* Add start button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/start.png"),
			START,
			150, 200, 357, 132
		)
	);

	/* Add Load Custom Level button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/loadcustomlevel.png"),
			LOAD_CUSTOM_LEVEL,
			550, 200, 357, 132
		)
	);

	/* Add level editor button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/leveleditor.png"),
			LEVEL_EDITOR,
			150, 350, 357, 132
		)
	);

	/* Add quit button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/quit.png"),
			QUIT,
			550, 350, 357, 132
		)
	);

	return ret;
}

/* ******************************* Shortcut to make the Load Custom Level menu */
Menu * New_LoadLevelMenu(Container *container) {
	/* Create menu with background texture */
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/MainMenu/background.png"));

	/* Add textbox for custom level path */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			350, 200, 64
		)
	);

	/* Add back button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/back.png"),
			BACK,
			50, 548, 357, 132
		)
	);

	/* Add start button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/start.png"),
			START,
			425, 280, 357, 132
		)
	);

	return ret;
}

/* */
Menu * New_LevelEditorMenu(Container *container) {
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/MainMenu/background.png"));

	/* Add "New Custom Level" button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/newlevel.png"),
			CREATE_CUSTOM_LEVEL,
			435, 200, 357, 132
		)
	);

	/* Add "Load Custom Level" button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/loadcustomlevel.png"),
			LOAD_CUSTOM_LEVEL,
			435, 350, 357, 132
		)
	);

	/* Add back button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/back.png"),
			BACK,
			50, 548, 357, 132
		)
	);



	return ret;
}



Menu * New_LevelEditorLoadCustomLevelMenu(Container *container) {
	/* Create menu with background texture */
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/MainMenu/background.png"));

	/* Add textbox for custom level path */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			350, 200, 64
		)
	);

	/* Add back button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/back.png"),
			BACK,
			850, 480, 357, 132
		)
	);

	/* Add start editing button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/loadcustomlevel.png"),
			LOAD_CUSTOM_LEVEL,
			850, 480 - 132 - 10, 357, 132
		)
	);

	return ret;
}

Menu * New_LevelEditorCreateCustomLevelMenu(Container *container) {
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/LoadLevel/background.png"));

	/* Add textbox for x size */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			350, 200, 10
		)
	);

	/* Add textbox for y size */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			450, 200, 10
		)
	);

	/* Add back button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/back.png"),
			BACK,
			850, 480, 357, 132
		)
	);

	/* Add start editing button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/createcustomlevel.png"),
			CREATE_CUSTOM_LEVEL,
			850, 480 - 132 - 10, 357, 132
		)
	);

	return ret;
}

void RunMenuManager(Container *container) {
	/* Main menu of program */
	Menu *MainMenu;
	/* Load and play a custom level menu */
	Menu *LoadLevelMenu;
	/* Level editor menu - create or load a custom level to edit */
	Menu *LevelEditorMenu;
	/* Create a custom level - enter width and height */
	Menu *LevelEditorCreateCustomLevelMenu;
	/* Load a custom level to edit - enter name of level */
	Menu *LevelEditorLoadCustomLevelMenu;
	/* The current menu being ran */
	Menu *CurrentMenu;

	/* The input from the user through the menu */
	MenuReturn MenuInput;
	/* Whether the loop should be running */
	bool running = true;
	/* The actual game */
	Game *game;

	/* Create all of the menus */
	MainMenu = New_MainMenu(container);
	LoadLevelMenu = New_LoadLevelMenu(container);
	LevelEditorMenu = New_LevelEditorMenu(container);
	LevelEditorCreateCustomLevelMenu = New_LevelEditorCreateCustomLevelMenu(container);
	LevelEditorLoadCustomLevelMenu = New_LevelEditorLoadCustomLevelMenu(container);

	/* Set the default menu */
	CurrentMenu = MainMenu;

	while (running) {
		/* Run the menu, get the input (button click) */
		MenuInput = Menu_Run(CurrentMenu, container);
		/* If we're on the main menu */
		if (CurrentMenu == MainMenu) {
			switch(MenuInput.action) {
				/* If the start button was pressed */
				case START:
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
					/* Close */
					running = false;
				break;
				/* If the Load Custom Level button was pressed */
				case LOAD_CUSTOM_LEVEL:
					/* Switch to LoadLevelMenu */
					CurrentMenu = LoadLevelMenu;
				break;
				case LEVEL_EDITOR:
					CurrentMenu = LevelEditorMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		/* If we're on the Load Level menu */
		} else if (CurrentMenu == LoadLevelMenu) {
			switch (MenuInput.action) {
				/* If the start button was pressed */
				case START:
					/* Start the custom level *********************************/
					/* Start a new game in CUSTOM_LEVEL mode using the text */
					game = New_Game(container, CUSTOM_LEVEL, MenuInput.text);
					/* Do nothing if Custom Level not found */
					if (!game) break;
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
		/* If we're on the Level Editor menu */
		} else if (CurrentMenu == LevelEditorMenu) {
			switch (MenuInput.action) {
				case BACK:
					CurrentMenu = MainMenu;
				break;
				case LOAD_CUSTOM_LEVEL:
					CurrentMenu = LevelEditorLoadCustomLevelMenu;
				break;
				case CREATE_CUSTOM_LEVEL:
					CurrentMenu = LevelEditorCreateCustomLevelMenu;
				break;
			}
		} else if (CurrentMenu == LevelEditorLoadCustomLevelMenu) {
			switch (MenuInput.action) {
				case BACK:
					CurrentMenu = LevelEditorMenu;
				break;
				case LOAD_CUSTOM_LEVEL:
//					Level *level = New_LevelByName(MenuInput.txt);
					/* TODO call the level editor with EDIT mode here */
				break;
			}
		} else if (CurrentMenu == LevelEditorCreateCustomLevelMenu) {
			switch (MenuInput.action) {
				case BACK:
					CurrentMenu = LevelEditorMenu;
				break;
				case CREATE_CUSTOM_LEVEL:
					/* TODO call the level editor with NEW mode here */
				break;
			}
		}
	}

	Menu_Destroy(MainMenu);
	Menu_Destroy(LoadLevelMenu);
	Menu_Destroy(LevelEditorMenu);
	Menu_Destroy(LevelEditorCreateCustomLevelMenu);
	Menu_Destroy(LevelEditorLoadCustomLevelMenu);


}
