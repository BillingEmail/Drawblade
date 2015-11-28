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
	ret->text = calloc(maxCharacters, sizeof(char));
	ret->text[0] = '\0';
	ret->texture = t;

	ret->renderRect.x = x;
	ret->renderRect.y = y;
	ret->renderRect.h = 46;
	ret->renderRect.w = 23 * maxCharacters;
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
	SDL_Surface *TextSurface;
	SDL_Texture *TextTexture;
	SDL_Color TextColor = {15, 15, 15};
	SDL_Rect TextRect;

	SDL_RenderCopy(container->renderer, t->texture->texture, NULL, &t->renderRect);
	if (t->text[0] == '\0') return;

	TextSurface = TTF_RenderText_Solid(container->font, t->text, TextColor);
	TextTexture = SDL_CreateTextureFromSurface(container->renderer, TextSurface);
	
	TextRect.x = t->renderRect.x;
	TextRect.y = t->renderRect.y;
	TextRect.w = TextSurface->w;
	TextRect.h = TextSurface->h;

//	SDL_FreeSurface(TextSurface);


	SDL_RenderCopy(container->renderer, TextTexture, NULL, &TextRect);
}

void Textbox_ReadInput(Textbox *t) {
	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_BACKSPACE && t->text[0] != '\0') {
				t->text[strlen(t->text) - 1] = '\0';
			}
		} else if (e.type == SDL_TEXTINPUT) {
			puts(e.text.text);
			puts(t->text);
			strcat(t->text, e.text.text);
		}
	}
}
