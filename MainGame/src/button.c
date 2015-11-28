#include "../include/button.h"

/* Create a new button with an action, size, and location */
Button * New_Button(Texture *t, Action action, int x, int y, int w, int h) {
	Button *ret = malloc(sizeof(Button));

	ret->texture = t;
	ret->action = action;

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
	return (container->mouse.leftClick &&
			container->mouse.x >= button->renderRect.x &&
			container->mouse.x <= button->renderRect.x + button->renderRect.w &&
			container->mouse.y >= button->renderRect.y &&
			container->mouse.y <= button->renderRect.y + button->renderRect.h);
}

/* Render a button */
void Button_Render(Button *button, Container *container) {
	Texture_Render(button->texture, container->renderer, button->renderRect.x, button->renderRect.y, NULL);
}
