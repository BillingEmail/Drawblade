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
//	char buffer[32] /* For textboxes */

	while (running) {
		Container_Refresh(container);
		for (int i = 0; i < m->buttonCount; i++) {
			if (Button_Clicked(m->buttons[i], container)) {
				ret.action = m->buttons[i]->action;
				running = false;
			}
		}
		/* SOMETHING WITH TEXT BOXES TODO TODO TODO use the buffer etc */
		Texture_Render(m->background, container->renderer, 0, 0, NULL);
		for (int i = 0; i < m->buttonCount; i++) {
			Button_Render(m->buttons[i], container);
		}
	}

	return ret;
}

Menu * New_MainMenu(Container *container) {
	/* Create menu with background texture */
	Menu *ret = New_Menu(New_Texture(container->renderer, "../assets/img/MainMenu/background.png"));

	/* Add start button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/MainMenu/start.png"),
			START,
			435, 200, 357, 132
		)
	);

	/* Add Load Custom Level button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/MainMenu/loadcustomlevel.png"),
			LOAD_CUSTOM_LEVEL,
			435, 350, 357, 132
		)
	);

	/* Add quit button */
	Menu_AddButton(
		ret,
		New_Button(
			New_Texture(container->renderer, "../assets/img/MainMenu/quit.png"),
			QUIT,
			435, 500, 357, 132
		)
	);

	return ret;
}
