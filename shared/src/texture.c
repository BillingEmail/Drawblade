/* texture.c - implementation of the type Texture
 * See texture.h for details.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/texture.h"

/* Create a new texture from an image path */
Texture * New_Texture(SDL_Renderer *renderer, char *path) {
	/* The pointer that will be returned */
	Texture *ret = NULL;

	/* Allocate memory for the Texture */
	ret = malloc(sizeof(Texture));

	/* Load an image into a surface */
	SDL_Surface *ImageSurface = IMG_Load(path);
	if (!ImageSurface) {
		fprintf(stderr, "Error loading image %s: %s\n", path, SDL_GetError());
		return NULL;
	}

	SDL_SetColorKey(ImageSurface, SDL_TRUE, SDL_MapRGB(ImageSurface->format, 0, 255, 255));

	/* Create a texture from the loaded surface */
	ret->texture = SDL_CreateTextureFromSurface(renderer, ImageSurface);
	if (!ret->texture) {
		fprintf(stderr, "Error creating texture from image: %s\n", SDL_GetError());
		return NULL;
	}
	/* Copy the width and height values from ImageSurface into the Texture's
	 * width and height.
	 */
	ret->w  = ImageSurface->w;
	ret->h = ImageSurface->h;

	/* We don't need the SDL_Surface after creating the texture from it.
	 * The ImageSurface is a software image.
	 */
	SDL_FreeSurface(ImageSurface);

	/* Return the created Texture (that has an SDL_Texture, width, and height) */
	return ret;
}

/* Destroy a texture previous made with New_Texture() */
void Destroy_Texture(Texture *T) {
	/* In case T was assigned to NULL - should happen after being destroyed */
	if (!T) {
		return;
	}

	/* destroy the sdl texture */
	SDL_DestroyTexture(T->texture);

	free(T);
	T = NULL;
}

/* Render a texture by itself */
void Texture_Render(Texture *t, SDL_Renderer *r, int x, int y, SDL_Rect *Camera) {
	if (t == NULL) {
		return;
	}
	
	/* Destination relative to window to render texture */
	SDL_Rect renderRect;
	/* Not fixed to the window - does not move with Camera */
	if (Camera) {
		renderRect.x = x - Camera->x;
		renderRect.y = y - Camera->y;
	/* Fixed to the window - such as the HUD, etc */
	} else {
		renderRect.x = x;
		renderRect.y = y;
	}
	/* Use width and height of texture */
	renderRect.w = t->w;
	renderRect.h = t->h;
	/* Add it to the renderer */
	SDL_RenderCopy(r, t->texture, NULL, &renderRect);
}
