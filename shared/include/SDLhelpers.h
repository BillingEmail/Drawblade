#ifndef SDLhelpers_h
#define SDLhelpers_h
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>



SDL_Window * MakeWindow(int width, int height);
SDL_Renderer * MakeRenderer(SDL_Window *window);
void KeyBoardUpdateCamera(SDL_Rect *Camera, const uint8_t *KeyboardState);
void PlayerUpdateCamera(SDL_Rect *Camera, CharacterType *ct, int instance_index);






#endif
