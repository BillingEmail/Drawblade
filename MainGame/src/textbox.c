#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/textbox.h"
#include "../../shared/include/texture.h"

/* Create a new textbox */
Textbox * New_Textbox(Texture *t, int x, int y, int maxCharacters) {
	Textbox *ret;

	ret = malloc(sizeof(Textbox));
	ret->text = malloc(maxCharacters * sizeof(char));

	ret->texture = t;

	ret->renderRect.x = x;
	ret->renderRect.y = y;
	ret->renderRect.h = 46;
	ret->renderRect.w = maxCharacters * 8;
	ret->maxCharacters = maxCharacters;

	return ret;
}

void Textbox_Destroy(Textbox *t) {
	Destroy_Texture(t->texture);
	free(t->text);
	free(t);
}

bool Textbox_Clicked(Textbox *textbox, Container *container) {
	return (container->mouse.leftClick &&
		container->mouse.x >= textbox->renderRect.x &&
		container->mouse.x <= textbox->renderRect.x + textbox->renderRect.w &&
		container->mouse.y >= textbox->renderRect.y &&
		container->mouse.y <= textbox->renderRect.y + textbox->renderRect.h);
}

void Textbox_Render(Textbox *t, Container *container) {
	SDL_RenderCopy(container->renderer, t->texture->texture, NULL, &t->renderRect);
}

void Textbox_ReadInput(Textbox *t) {
/*	SDL_Event e;
	bool renderText = false;

	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_TEXTINPUT) {
			strcat(t->text, e.text.text);
		}
*/


}
