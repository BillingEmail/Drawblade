#ifndef SDLhelpers_h
#define SDLhelpers_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


/* Wraps all of the SDL objects into one struct */
typedef struct _SDLWrapper {
	SDL_Window *  window;
	SDL_Renderer * renderer;
	SDL_Rect * camera;
	uint8_t * keyboardstate;
} SDLWrapper;


/* 
 * All of the SDL functions are now wrapped into these functions
 * You now can call these functions, and they will handle SDL objects
 * in our code 
 */

SDLWrapper * New_Wrapper(int width, int height);
void SDLWrapper_Destroy(SDLWrapper * wrapper);
void SDLWrapper_EditorRefresh(SDLWrapper * wrapper);

/*  Functions for making parts of the wrapper */
SDL_Window * MakeWindow(int width, int height);
SDL_Renderer * MakeRenderer(SDL_Window *window);

/*  Functions for updating the camera depending on the situation */
void KeyBoardUpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState);
void PlayerUpdateCamera(SDL_Rect *Camera, CharacterType *ct, int instance_index);






#endif
