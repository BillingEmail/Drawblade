#ifndef BUTTON_H
#define BUTTON_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

/* A signal that a button returns when it is clicked */
typedef enum _action {
	START, LOAD_CUSTOM_LEVEL, QUIT, BACK, CREATE_CUSTOM_LEVEL, LEVEL_EDITOR, NEXT, START_EDITING, CANCEL, SAVE
} Action;

/* A button used on a Menu */
typedef struct _button {
	Texture *texture; /* The image of the button */
	Action action; /* It's action */
	SDL_Rect renderRect; /* x, y, w, h */
} Button;

/* Create a new button */
Button * New_Button(Texture *t, Action action, int x, int y, int w, int h);

/* Destroy a button */
void Button_Destroy(Button *button);

/* Whether or not the mouse is clicking a button, is called every frame */
bool Button_Clicked(Button *button, Container *container);

/* Render a button to the screen */
void Button_Render(Button *button, Container *container);

#endif
