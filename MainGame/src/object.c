/* objecttype.c - implementation for type ObjectType
 *
 * See objecttype.h for details.
 */

#include <SDL2/SDL.h>
#include "../include/object.h"

/* Create a new Object, with a spritesheet already created */
ObjectType * New_ObjectType(Spritesheet *spritesheet, int w, int h) {

	ObjectType *ret = malloc(sizeof(ObjectType));
	if (!ret) {
		fprintf(stderr, "Error creating object\n");
		return NULL;
	}

	ret->spritesheet = spritesheet;
	ret->size.w = w;
	ret->size.h = h;

	/* Create the animations for the object */
	/* Make the animations list */
	ret->animations = malloc(spritesheet->animation_count * sizeof(SDL_Rect *));
	for (int i = 0; i < spritesheet->animation_count; i++) {
		/* Make the list of sprites in the animation */
		ret->animations[i] = malloc(spritesheet->frames_in_animation[i] * sizeof(SDL_Rect));
		for (int k = 0; k < spritesheet->frames_in_animation[i]; k++) {
			ret->animations[i][k].x = w * k;
			ret->animations[i][k].y = h * i;
			ret->animations[i][k].w = w;
			ret->animations[i][k].h = h;
		}
	}

	/* Create room for 2 instances - this can be increased when objects are added */
	ret->instances = malloc(2 * sizeof(Object));
	ret->instances_size = 2;
	ret->instance_count = 0;

	return ret;
}

/* Create a new object of an ObjectType ot */
void ObjectType_AddObject(ObjectType *ot, int x, int y, int default_animation, int default_sprite) {
	/* Make sure ot->instances is large enough to have another object */
	if (ot->instance_count >= ot->instances_size - 1) {
		/* Double the size of ot->instances */
		ot->instances = realloc(ot->instances, ot->instances_size * 2 * sizeof(Object));
		ot->instances_size *= 2;
	}

	SDL_Rect *dstrect = &ot->instances[ot->instance_count].dstrect;
	/* Copy the passed initial position */
	dstrect->x = x;
	dstrect->y = y;
	dstrect->w = ot->size.w;
	dstrect->h = ot->size.h;
	
	//Shortcut to hitboxes used in update function
	SDL_Rect *hitboxes = ot->instances[ot->instance_count].hitboxes;
	
	//In the following code, the new pointer is a shortcut to each hitbox
	//It then sets the hitboxes to that space

	SDL_Rect *temprect = &hitboxes[TOP_HITBOX];
	temprect->x = x;
	temprect->y = y;
	temprect->w = ot->size.w;
	temprect->h = 8;

	temprect = &hitboxes[LEFT_HITBOX];
	temprect->x = x;
	temprect->y = y + 8;
	temprect->w = 8;
	temprect->h = ot->size.h - 16;

	temprect = &hitboxes[RIGHT_HITBOX];
	temprect->x = x + ot->size.w - 8;
	temprect->y = y + 8;
	temprect->w = 8;
	temprect->h = ot->size.h - 16;

	temprect = &hitboxes[BOTTOM_HITBOX];
	temprect->x = x;
	temprect->y = y + ot->size.h - 8;
	temprect->w = ot->size.w;
	temprect->h = 8;



	/* Copy the passed initial animation and initial sprite */
	ot->instances[ot->instance_count].animation = default_animation;
	ot->instances[ot->instance_count].sprite_index = default_sprite;
	ot->instance_count++;
}

/* Set the animation for an object */
void ObjectType_SetObjectAnimation(ObjectType *ot, int instance_index, int animation) {
	ot->instances[instance_index].animation = animation;
}

/* Change the object's sprite to the following sprite in the animation */
void ObjectType_ObjectNextSprite(ObjectType *o, int instance_index) {
	/* Increment the instance's sprite index */
	o->instances[instance_index].sprite_index++;

	/* If the sprite index of the instance is greater than the instance's current animation's size, restart the animation */
	if (o->instances[instance_index].sprite_index >= o->spritesheet->frames_in_animation[o->instances[instance_index].animation]) {
		o->instances[instance_index].sprite_index = 0;
	}
}

/* Render an instance of ObjectType */
void ObjectType_RenderObject(ObjectType *ot, int instance_index, Container *container) {
	SDL_Rect *objectrefrect = &ot->instances[instance_index].dstrect;
	SDL_Rect dstrect = {
		objectrefrect->x - container->camera->x,
		objectrefrect->y - container->camera->y,
		objectrefrect->w,
		objectrefrect->h
	};
	
	SDL_RenderCopy(
		container->renderer,
		ot->spritesheet->texture->texture,
		&ot->animations[ot->instances[instance_index].animation][ot->instances[instance_index].sprite_index],
		&dstrect
	);
}

/* Destroy an ObjectType and all of its sub parts */
void Destroy_ObjectType(ObjectType *ot) {
	for (int i = 0; i < ot->spritesheet->animation_count; i++) {
		free(ot->animations[i]);
	}
	free(ot->animations);

	free(ot->instances);

	Destroy_Spritesheet(ot->spritesheet);
	free(ot);
	ot = NULL;
}
