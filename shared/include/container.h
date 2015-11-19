#ifndef SDLhelpers_h
#define SDLhelpers_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/* Wraps all of the SDL objects into one struct */
typedef struct _SDL_container {
	SDL_Window *  window;
	SDL_Renderer * renderer;
	SDL_Rect * camera;
	uint8_t * keyboardstate;
} Container;


/* 
 * Create a new container
 */

Container * New_Container(void);

void Container_Destroy(Container *c);

void Container_EditorRefresh(Container *c);

/*  Functions for making parts of the wrapper */
SDL_Window * MakeWindow(int width, int height);

SDL_Renderer * MakeRenderer(SDL_Window *window);

/*  Functions for updating the camera depending on the situation */
/* Update the camera with the arrow keys */
void KeyBoardUpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState);

/* update the camera using player position */
void PlayerUpdateCamera(Player *p, SDL_Rect *Camera);

#endif
