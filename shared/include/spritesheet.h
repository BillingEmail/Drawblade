/* spritesheet.h - type definition for Spritesheet.
 *
 * A spritesheet holds a texture that will be used as a spritesheet for
 * an object. It also holds the amount of animations that are in the
 * spritesheet, and an array of how many frames are in each animation.
 */

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "texture.h"

/* A spritesheet for an object */
typedef struct {
	Texture *texture;          /* The actual spritesheet for the object */

	int animation_count;       /* The amount of animations in a spritesheet */

	int *frames_in_animation;  /* An array, each member denoting how many frames
	                            * are in an animation. For example, if
	                            * frames_in_animation[3] is 5, then an object's
	                            * fourth animation has 5 different frames.
	                            */
} Spritesheet;

/* Create a new spritesheet from a texture */
Spritesheet * New_Spritesheet(Texture *t, int animations, ...);

/* Destroy a spritesheet */
void Destroy_Spritesheet(Spritesheet *s);


#endif
