/* button.c - implementation of a button to be used with a Menu
 *
 * Author: Sean Rapp
 */

#include "../include/button.h"

/* Create a new button with an action, size, and location */
Button * New_Button(Texture *t, Action action, int x, int y, int w, int h) {
	Button *ret = malloc(sizeof(Button));

	/* Gives the button a texture you passed in */
	ret->texture = t;
	/* Tells the button which screen it should open when clicked */
	ret->action = action;

	/* the size and coordinates of the button */
	ret->renderRect.x = x;
	ret->renderRect.y = y;
	ret->renderRect.w = w;
	ret->renderRect.h = h;

	return ret;
}

/* Destroy a button */
void Button_Destroy(Button *b) {
	Destroy_Texture(b->texture);
	free(b); /* freebie */
}

/* Return true if the mouse is clicking the button */
bool Button_Clicked(Button *button, Container *container) {
	/* Checks if you are left clicking within the bounds of the button */
	return (container->mouse.leftClick &&
			container->mouse.x >= button->renderRect.x &&
			container->mouse.x <= button->renderRect.x + button->renderRect.w &&
			container->mouse.y >= button->renderRect.y &&
			container->mouse.y <= button->renderRect.y + button->renderRect.h);
}

/* Render a button */
void Button_Render(Button *button, Container *container) {
	/* Renders the button's texture at its coordinates */
	Texture_Render(button->texture, container->renderer, button->renderRect.x, button->renderRect.y, NULL);
}
