/* spritesheet.c - implementation of type Spritesheet.
 *
 * See spritesheet.h for details.
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../include/texture.h"
#include "../include/spritesheet.h"

/* Create a new spritesheet from a texture, using an animation count,
 * and a list of how many frames are in each animation.
 */
Spritesheet * New_Spritesheet(Texture *t, int animation_count, ...) {
	Spritesheet *ret;
	va_list frame_counts;
	int i = 0;

	ret = malloc(sizeof(Spritesheet));
	if (!ret) {
		fprintf(stderr, "Could not create spritesheet: could not allocate memory\n");
		return NULL;
	}
	ret->texture = t;
	ret->animation_count = animation_count;
	ret->frames_in_animation = malloc(animation_count * sizeof(int));

	va_start(frame_counts, animation_count);
	for (i = 0; i < animation_count; i++) {
		ret->frames_in_animation[i] = va_arg(frame_counts, int);
	}
	va_end(frame_counts);

	return ret;
}

/* Destroy a spritesheet */
void Destroy_Spritesheet(Spritesheet *s) {
	if (!s) {
		fprintf(stderr, "Warning: multiple free of spritesheet\n");
		return;
	}
	Destroy_Texture(s->texture);
	free(s->frames_in_animation);
	free(s);
	s = NULL;
}
