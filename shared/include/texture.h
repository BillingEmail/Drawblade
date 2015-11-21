/* texture.h - type definition for Texture
 *
 * The Texture is used primarily to hold an image
 * that will be rendered to an object. The object may
 * use the entire texture, or just a clip from the texture.
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>

/* Type: Texture */
typedef struct {
	SDL_Texture *texture; /* Actual hardware texture */
	int w; /* Width of texture */
	int h; /* Height of texture */
} Texture;

/* Texture Functions */

/* Create a new texture from an image path */
Texture * New_Texture(SDL_Renderer *r, char *path);

/* Destroy a texture */
void Destroy_Texture(Texture *t);

/* Render a texture at a position */
void Texture_Render(Texture *t, SDL_Renderer *r, int x, int y, SDL_Rect *Camera);

#endif
