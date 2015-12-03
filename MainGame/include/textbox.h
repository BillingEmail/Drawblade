/* textbox.h - Data type for a textbox for a menu - reads in text from keyboard
 *
 * Author: Sean Rapp
 */

#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SDL2/SDL.h>
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

/* A textbox */
typedef struct _textbox {
	Texture *texture; /* The texture for the textbox */
	char *text; /* The text in the textbox */
	SDL_Rect renderRect;
	int maxCharacters; /* maximum characters the textbox can hold 
	                    * - determines the length */
} Textbox;

/* Create a new textbox */
Textbox * New_Textbox(Texture *t, int x, int y, int maxCharacters);

/* Destroy a textbox */
void Textbox_Destroy(Textbox *t);

/* Whether or not the mouse is clicking in the textbox */
bool Textbox_Clicked(Textbox *t, Container *container);

/* Whether the textbox should recieve keyboard input */
bool Textbox_Unfocused(Textbox *t, Container *container);

/* Render a textbox and it's current text to the screen */
void Textbox_Render(Textbox *button, Container *container);

/* Read keyboard input, change t->text */
void Textbox_ReadInput(Textbox *t);

#endif
