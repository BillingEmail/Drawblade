/* object.h - type definition for ObjectType
 *
 * An object is the basic building block for anything that will be
 * part of the world. Every block, wall, character, and the player
 * all have Objects in them. However, blocks are JUST an object,
 * while something like a character CONTAINS a block.
 *
 * The ObjectType is used to create a type of object. Every type
 * of object has the same spritesheet and animations. The ObjectType holds a
 * list of rectangles as well - these represent each instance of the object.
 * For example, an ObjectType called 'brick' can be created, loading the
 * spritesheet and animations, and then a list of bricks can be created. Each
 * brick itself is just a location (x,y) and size (width,height). The
 * ObjectType holds the rest. This allows for the creation of only a single
 * ObjectType - the brick - and the creation of an infinite (providing memory)
 * amount of bricks.
 *
 * Since the ObjectType holds a list of objects, and an object
 */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../../shared/include/texture.h"
#include "../../shared/include/spritesheet.h"
#include "../../shared/include/container.h"

enum {
	LEFT_HITBOX,
	RIGHT_HITBOX,
	TOP_HITBOX,
	BOTTOM_HITBOX
};

/* The Object struct - an instance of an ObjectType */
typedef struct _object {
	SDL_Rect dstrect;      /* The destination rectangle for the object - where
	                        * it is going to be rendered.
	                        * .x, .y: The position/location of the object;
	                        * .w, .h: The dimensions (width and height) of the
	                        * object
	                        */

	SDL_Rect hitboxes[4];  /* Top, left, right, and bottom hitboxes */ 

	int *sprite_index;      /* The index of the current sprite in the Object's
	                        * ObjectType's animations[animation] */


	int animation;         /* The current animation of the object. This will
	                        * be used as the index for animations to determine
	                        * which animation to play. For example, if
	                        * animation is 3, then animations[3] of the
	                        * Object's ObjectType will be played.
	                        */

	int lastAnimation;

} Object;

/* The ObjectType struct */
typedef struct _objecttype {
	Spritesheet *spritesheet;  /* Each type of object has a spritesheet, all objects
	                            * of the same type have their spritesheet member set
	                            * to the same value.
	                            */

	SDL_Rect **animations; /* A 2-dimensional, possible jagged, array of rects.
	                        * Each rect is a source rectangle clip for the
	                        * spritesheet. If an object has 4 animations,
	                        * animations[0 through 3] are each animation.
	                        * For example, animations[1] is an object's
	                        * second animation, and animations[1][2] is
	                        * the third sprite of the object's second
	                        * animation.
	                        */

	Object *instances;     /* This is a list of the instances of the ObjectType.
	                        * Each holds the location (x,y) and size (width,
	                        * height), the current sprite of the object, and
	                        * the current animation of the object. This allows
	                        * multiple objects of the same type to be playing
	                        * different animations.
	                        */

	int instance_count;    /* The count of how many instances have been created,
	                        * i.e., how many Objects have been added to the
	                        * ObjectType
	                        */

	int instances_size;    /* The amount of memory currently held by instances */

	struct {
		int w;
		int h;
	} size;                /* The size, used for the dstrect for objects etc */

} ObjectType;

/* Functions for ObjectType */

/* Create a new ObjectType from a spritesheet and whether the object has
 * full collision.
 */
ObjectType * New_ObjectType(
	Spritesheet *spritesheet, /* The spritesheet to be used for all instances */
	int w,                    /* Width of object */
	int h                     /* Height of object */
);

/* Destroy an object type, including it's spritesheet, the spritesheet's
 * texture, and all instances of the ObjectType.
 */
void Destroy_ObjectType(ObjectType *ot);

/* Add another instance of the ObjectType to the list of instances */
void ObjectType_AddObject(
	ObjectType *ot,        /* The ObjectType                                    */
	int x,                 /* The original x-position of the object             */ 
	int y                 /* The original y-position of the object             */
);

/* Return the count of object in an ObjectType */
//int ObjectType_Count(ObjectType *ot);

#define ObjectType_Count(OT) (OT)->instance_count


/* Render a specific instance of an ObjectType */
void ObjectType_RenderObject(ObjectType *ot, int instance_index, unsigned int dt, Container *c);

/* Set the animation of an object. Typically, an enum for an animation specific
 * to the object type will be used.
 */
void ObjectType_SetObjectAnimation(ObjectType *ot, int instance_index, int animation);

/* Increment the current sprite of the object to the next sprite in the
 * animation, resetting to the first sprite of the animation when the
 * sprite passes the final sprite of the animation.
 */
void ObjectType_ObjectNextSprite(ObjectType *ot, int instance_index);

/* Destroy an object */
void Destroy_Object(Object *o);

void ObjectType_ResetSpriteIndexes(ObjectType *o, int ii, int animation);

#endif
