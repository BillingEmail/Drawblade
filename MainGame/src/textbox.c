/* textbox.c - A textbox to be used in menus
 *
 * Author: Sean Rapp
 */


#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../include/textbox.h"
#include "../../shared/include/texture.h"

/* Create a new textbox */
Textbox * New_Textbox(Texture *t, int x, int y, int maxCharacters) {
	Textbox *ret;

	/* Create the textbox */
	ret = malloc(sizeof(Textbox));
	/* Create the space for the input text */
	ret->text = calloc(maxCharacters, 1);
	/* Default text to "" */
	ret->text[0] = '\0';
	/* Reference texture */
	ret->texture = t;

	/* Create the render rectangle for the textbox */
	ret->renderRect.x = x;
	ret->renderRect.y = y;
	ret->renderRect.h = 46;
	/* Length of textbox depends on max characters */
	ret->renderRect.w = 8 * maxCharacters;
	/* Copy max characters value */
	ret->maxCharacters = maxCharacters;

	return ret;
}

/* Destroy a textbox */
void Textbox_Destroy(Textbox *t) {
	Destroy_Texture(t->texture);
	free(t->text);
	free(t);
}

/* Return if the mouse is clicking inside of the textbox */
bool Textbox_Clicked(Textbox *textbox, Container *container) {
	return (container->mouse.leftClick &&
		container->mouse.x >= textbox->renderRect.x &&
		container->mouse.x <= textbox->renderRect.x + textbox->renderRect.w &&
		container->mouse.y >= textbox->renderRect.y &&
		container->mouse.y <= textbox->renderRect.y + textbox->renderRect.h);
}

/* Render a textbox */
void Textbox_Render(Textbox *t, Container *container) {
	/* The surface - an intermediate between font/text and a texture */
	SDL_Surface *TextSurface;
	/* Final texture of the text */
	SDL_Texture *TextTexture;
	/* The color of the text */
	SDL_Color TextColor = {145, 145, 145, 240};
	/* The final rectangle to render the text at */
	SDL_Rect TextRect;

	/* Render the background of the textbox */
	SDL_RenderCopy(container->renderer, t->texture->texture, NULL, &t->renderRect);
	/* End here if there is no text in the texbtox */
	if (t->text[0] == '\0') return;

	/* Create a texture from a font and string */
	TextSurface = TTF_RenderText_Solid(container->font, t->text, TextColor);
	TextTexture = SDL_CreateTextureFromSurface(container->renderer, TextSurface);

	/* Use the size of the entire string to make the final render rect */
	/* Center justify text in textbox */
	TextRect.x = t->renderRect.x + t->renderRect.w / 2 - strlen(t->text) * 10;
	/* Left justify text in textbox */
//	TextRect.x = t->renderRect.x;
	TextRect.y = t->renderRect.y;
	TextRect.w = TextSurface->w;
	TextRect.h = TextSurface->h;
	/* Free the no longer needed intermediate */
	SDL_FreeSurface(TextSurface);
	
	/* Copy the texture to the rendering context */
	SDL_RenderCopy(container->renderer, TextTexture, NULL, &TextRect);
}

/* Read keyboard input into the textbox */
void Textbox_ReadInput(Textbox *t) {
	/* Contains information of all types of input */
	SDL_Event event;

	/* While keys are being pressed */
	while (SDL_PollEvent(&event)) {
		/* On a keypress */
		if (event.type == SDL_KEYDOWN) {
			/* If the backspace key is pressed and the textbox isn't empty */
			if (event.key.keysym.sym == SDLK_BACKSPACE && t->text[0] != '\0') {
				/* Remove the final character from the text */
				t->text[strlen(t->text) - 1] = '\0';
			}
		/* If there is text input */
		} else if (event.type == SDL_TEXTINPUT) {
			/* If the textbox isn't full */
			if (strlen(t->text) < t->maxCharacters) {
				/* Concatenate the input to the text */
				strcat(t->text, event.text.text);
			}
		}
	}
}
