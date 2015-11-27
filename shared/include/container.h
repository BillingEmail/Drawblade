/* container.h - A container to hold commonly-used interfacing objects, 
 * such as the window, renderer, and input such as the keyboard and mouse.
 */

#ifndef CONTAINER_H
#define CONTAINER_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/* Contains commonly-used interfacing objects */
typedef struct _SDL_container {
	SDL_Window *window;       /* The window                                   */
	SDL_Renderer *renderer;   /* Rendering context for the window             */
	SDL_Rect *camera;         /* The camera - used for rendering images       */
	                          /* relative to some perspective                 */

	const uint8_t *keyboardstate;   /* The keyboardstate - a list of all of the     */
	                          /* keys and whether or not they are pressed.    */

	struct {                  /* The mouse:                                   */
		int x;                /* The coordinates of the mouse, relative to    */
		int y;                /* the top-left (0,0) corner of the window      */
		bool rightClick;      /* Whether the right mouse button is pressed    */
		bool leftClick;       /* Whether the left mouse button is pressed     */
	} mouse;

	TTF_Font *font;

} Container;

/* Create a new container (Creating a new window, rendering context, etc */
Container * New_Container(int SCREEN_WIDTH, int SCREEN_HEIGHT);

/* Safely close the window -- destroys rendering context but NOT any textures */
void Container_Destroy(Container *container);

/* Refresh the renderer, keyboardstate, and mouse */
void Container_Refresh(Container *container);

/* Create a window using a width and height */
SDL_Window * New_Window(int width, int height);

/* Create the rendering context for the window */
SDL_Renderer * New_Renderer(SDL_Window *window);

/* Update the camera with the arrow keys -- used in level editor*/
void Container_KeyBoardUpdateCamera(Container *c);

#endif
