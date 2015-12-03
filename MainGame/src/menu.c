/* menu.c - A simple GUI with images, buttons, and textboxes
 * Also includes shortcuts to create the menus used in the program.
 * Disgusting organization, read at your discretion.
 *
 * Author: Sean Rapp
 */


#include <stdbool.h>
#include <stdlib.h>
#include "../include/game.h"
#include "../include/button.h"
#include "../include/textbox.h"
#include "../include/menu.h"
#include "../../shared/include/level.h"
#include "../../LevelEditor/include/leveleditor.h"

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

	ret->images = malloc(sizeof(Image *));
	ret->imageCount = 0;
	ret->imagesSize = 1;

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

void Menu_AddImage(Menu *m, Texture *t, int x, int y) {
	/* Resize buttons array if cap is reached, increase cap accordingly */
	if (m->imageCount == m->imagesSize) {
		m->images = realloc(m->images, m->imagesSize * 2 * sizeof(Image *));
		m->imagesSize *= 2;
	}
	/* Add the button */
	m->images[m->imageCount] = malloc(sizeof(Image));
	m->images[m->imageCount]->x = x;
	m->images[m->imageCount]->y = y;
	m->images[m->imageCount]->texture = t;
	m->imageCount++;
}


/* Destroy a menu from existence, all of its buttons and textboxes included */
void Menu_Destroy(Menu *m) {
	for (int i = 0; i < m->buttonCount; i++) {
		Button_Destroy(m->buttons[i]);
	}
	for (int i = 0; i < m->textboxCount; i++) {
		Textbox_Destroy(m->textboxes[i]);
	}
	for (int i = 0; i < m->imageCount; i++) {
		Destroy_Texture(m->images[i]->texture);
		free(m->images[i]);
	}
	free(m->buttons);
	free(m->textboxes);
	free(m->images);
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
		for (int i = 0; i < m->imageCount; i++) {
			Texture_Render(m->images[i]->texture, container->renderer, m->images[i]->x, m->images[i]->y, NULL);
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

	/* Add the title image */
	Menu_AddImage(
		ret,
		New_Texture(container->renderer, "../assets/img/Menus/MainMenu/title.png"),
		2, 2
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
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/createcustomlevel.png"),
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
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/startediting.png"),
			START_EDITING,
			850, 480 - 132 - 10, 357, 132
		)
	);

	return ret;
}

/* Enterprise quality */
Menu * New_LevelEditorCreateCustomLevelHorizontalSizeMenu(Container *container) {
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/LoadLevel/background.png"));

	/* Add textbox for x size */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			480, 278, 10
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
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/next.png"),
			NEXT,
			850, 480 - 132 - 10, 357, 132
		)
	);

	/* Add "Enter Width" image */
	Menu_AddImage(
		ret,
		New_Texture(container->renderer, "../assets/img/Menus/enterwidth.png"),
		400, 200
	);

	return ret;
}


Menu * New_SaveLevelMenu(Container *container) {
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/MainMenu/background.png"));

	/* Enter level name textbox */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			350, 200, 64
		)
	);

	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/save.png"),
			SAVE,
			425, 280, 357, 132
		)
	);

	Menu_AddImage(
		ret,
		New_Texture(container->renderer, "../assets/img/Menus/enterlevelname.png"),
		450, 20
	);

	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/cancel.png"),
			CANCEL,
			425, 420, 357, 132
		)
	);


	return ret;
}

/* Enterprise quality */
Menu * New_LevelEditorCreateCustomLevelVerticalSizeMenu(Container *container) {
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/Menus/LoadLevel/background.png"));

	/* Add textbox for x size */
	Menu_AddTextbox(
		ret,
		New_Textbox(
			New_Texture(container->renderer, "../assets/img/Menus/textbox.png"),
			480, 278, 10
		)
	);

	/* Add Back button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/back.png"),
			BACK,
			850, 480, 357, 132
		)
	);

	/* Add Next button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/Menus/Buttons/startediting.png"),
			START_EDITING,
			850, 480 - 132 - 10, 357, 132
		)
	);

	/* Add "Enter Height" image */
	Menu_AddImage(
		ret,
		New_Texture(container->renderer, "../assets/img/Menus/enterheight.png"),
		400, 200
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
	/* Create a custom level - enter height */
	Menu *LevelEditorCreateCustomLevelHorizontalSizeMenu;
	/* enter width */
	Menu *LevelEditorCreateCustomLevelVerticalSizeMenu;
	/* Load a custom level to edit - enter name of level */
	Menu *LevelEditorLoadCustomLevelMenu;
	/* The menu to save a level after editing it */
	Menu *LevelEditorSaveLevelMenu;
	/* The current menu being ran */
	Menu *CurrentMenu;

	/* The input from the user through the menu */
	MenuReturn MenuInput;
	/* Whether the loop should be running */
	bool running = true;
	/* The actual game */
	Game *game;

	/* potentially used for creating a new level */
	int width, height;
	Level *level;

	/* Create all of the menus */
	MainMenu = New_MainMenu(container);
	LoadLevelMenu = New_LoadLevelMenu(container);
	LevelEditorMenu = New_LevelEditorMenu(container);
	LevelEditorCreateCustomLevelHorizontalSizeMenu = New_LevelEditorCreateCustomLevelHorizontalSizeMenu(container);
	LevelEditorCreateCustomLevelVerticalSizeMenu = New_LevelEditorCreateCustomLevelVerticalSizeMenu(container);
	LevelEditorLoadCustomLevelMenu = New_LevelEditorLoadCustomLevelMenu(container);
	LevelEditorSaveLevelMenu = New_SaveLevelMenu(container);

	/* Set the default menu */
	CurrentMenu = MainMenu;


	unsigned int CurrentTime, LastTime = 0, dt;
	unsigned int delay;

	while (running) {
		MenuInput = Menu_Run(CurrentMenu, container);
		CurrentTime = SDL_GetTicks();
		dt = CurrentTime - LastTime;
		LastTime = CurrentTime;

		delay += dt;
		if (delay < 500) {
			continue;
		} else {
			delay = 0;
		}
	
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
				/* If back is pressed, go to main menu */
				case BACK:
					CurrentMenu = MainMenu;
				break;
				/* If the Load Custom Level button is pressed */
				case LOAD_CUSTOM_LEVEL:
					CurrentMenu = LevelEditorLoadCustomLevelMenu;
				break;
				/* If the user wants to create a new level */
				case CREATE_CUSTOM_LEVEL:
					CurrentMenu = LevelEditorCreateCustomLevelHorizontalSizeMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;

			}
		/* If w're on the Load Custom Level to Edit menu */
		} else if (CurrentMenu == LevelEditorLoadCustomLevelMenu) {
			switch (MenuInput.action) {
				/* Go back to Level editor main menu */
				case BACK:
					CurrentMenu = LevelEditorMenu;
				break;
				case START_EDITING:
					level = New_LevelByName(MenuInput.text);
					Level_Edit(level, container);
					CurrentMenu = LevelEditorSaveLevelMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		/* If we're getting the width of the level to make */
		} else if (CurrentMenu == LevelEditorCreateCustomLevelHorizontalSizeMenu) {
			switch (MenuInput.action) {
				case BACK:
					CurrentMenu = LevelEditorMenu;
				break;
				case NEXT:
					width = atoi(MenuInput.text);
					CurrentMenu = LevelEditorCreateCustomLevelVerticalSizeMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		/* If we're getting the height of the level to make */
		} else if (CurrentMenu == LevelEditorCreateCustomLevelVerticalSizeMenu) {
			switch (MenuInput.action) {
				case BACK:
					CurrentMenu = LevelEditorCreateCustomLevelHorizontalSizeMenu;
				break;
				case START_EDITING: 
					height = atoi(MenuInput.text);
					level =  New_BlankLevel(width, height);
					Level_Edit(level, container);
					CurrentMenu = LevelEditorSaveLevelMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		} else if (CurrentMenu == LevelEditorSaveLevelMenu) {
			switch(MenuInput.action) {
				case CANCEL:
					CurrentMenu = MainMenu;
				break;
				case SAVE:
					CurrentMenu = MainMenu;
					Level_SaveByName(level, MenuInput.text);
					CurrentMenu = MainMenu;
				break;
				default:
					fprintf(stderr, "Internal error: %s:%s:%d\n", __FILE__, __func__, __LINE__);
				break;
			}
		}
	}

	Menu_Destroy(MainMenu);
	Menu_Destroy(LoadLevelMenu);
	Menu_Destroy(LevelEditorMenu);
	Menu_Destroy(LevelEditorSaveLevelMenu);
	Menu_Destroy(LevelEditorCreateCustomLevelVerticalSizeMenu);
	Menu_Destroy(LevelEditorCreateCustomLevelHorizontalSizeMenu);
	Menu_Destroy(LevelEditorLoadCustomLevelMenu);
}
