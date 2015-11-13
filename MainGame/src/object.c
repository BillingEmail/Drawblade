/* objecttype.c - implementation for type ObjectType
 *
 * See objecttype.h for details.
 */

#include <SDL2/SDL.h>
#include "../include/object.h"


/* Create a new Object, with a spritesheet already created */
ObjectType * New_ObjectType(
	Spritesheet *spritesheet,
	bool collision,
	int w,
	int h) {

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

	SDL_Rect *hitboxes = ot->instances[ot->instance_count].hitboxes;
	/* Create the 4 (top, left, right, bottom) hitboxes */
	/* Make a crafty loop for this at some point */
	hitboxes[TOP_HITBOX].x = x;
	hitboxes[TOP_HITBOX].y = y;
	hitboxes[TOP_HITBOX].w = ot->size.w;
	hitboxes[TOP_HITBOX].h = 2;

	hitboxes[LEFT_HITBOX].x = x;
	hitboxes[LEFT_HITBOX].y = y;
	hitboxes[LEFT_HITBOX].w = 2;
	hitboxes[LEFT_HITBOX].h = ot->size.h;

	hitboxes[RIGHT_HITBOX].x = x + ot->size.w - 2;
	hitboxes[RIGHT_HITBOX].y = y;
	hitboxes[RIGHT_HITBOX].w = 2;
	hitboxes[RIGHT_HITBOX].h = ot->size.h;

	hitboxes[BOTTOM_HITBOX].x = x;
	hitboxes[BOTTOM_HITBOX].y = y + ot->size.h - 2;
	hitboxes[BOTTOM_HITBOX].w = ot->size.w;
	hitboxes[BOTTOM_HITBOX].h = 2;	



	/* Copy the passed initial animation and initial sprite */
	ot->instances[ot->instance_count].animation = default_animation;
	ot->instances[ot->instance_count].sprite_index = default_sprite;
	ot->instance_count++;
}

/* Returns the omount of objects in an object type */
//int ObjectType_Count(ObjectType *ot) {
//	return ot->instance_count;
//}

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
void ObjectType_RenderObject(ObjectType *ot, SDL_Renderer *renderer, int instance_index, SDL_Rect *Camera) {
	SDL_Rect *objectrefrect = &ot->instances[instance_index].dstrect;
	SDL_Rect dstrect = {
		objectrefrect->x - Camera->x,
		objectrefrect->y - Camera->y,
		objectrefrect->w,
		objectrefrect->h
	};
	
	SDL_RenderCopy(
		renderer,
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

/* Check collision between two objects */
int * ObjectType_CheckCollision(ObjectType *ot1, ObjectType *ot2,
		int ii1, int ii2) {
	/* Holds the first and second hitbox indicators
	 * (could be {TOP_HITBOX, BOTTOM_HITBOX} if object1's top hits object2's
	 * bottom. heh.
	 */
	int *ret = malloc(2 * sizeof(int));

	/* Check every single combination of hitbox rectangles... efficiently... */
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			if (SDL_IntersectRect(&ot1->instances[ii1].hitboxes[k],
					&ot2->instances[ii2].hitboxes[i], NULL)) {
				*ret = k;
				ret[1] = i;
				return ret;
			}
		}
	}

	return NULL;
}	
