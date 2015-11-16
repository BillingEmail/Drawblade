#ifndef SDLhelpers_h
#define SDLhelpers_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



SDL_Window * MakeWindow(int width, int height);
SDL_Renderer * MakeRenderer(SDL_Window *window);
void UpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState);







#endif
