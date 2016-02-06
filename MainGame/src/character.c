/* character.c - Implementation for CharacterType
 *
 * See character.h for details
 *
 * Authors: Sean Rapp, Satya Patel
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/character.h"
#include "../include/object.h"
#include "../include/behavior.h"
#include "../../shared/include/container.h"

/* 
 * Create a new CharacterType
 * A charactertype is basically a dynamic array of all of the instances of a type of enemy
 * That holds all of the default information for an enemy, including its default HP, its default spritesheet, etc
 * Since every Character has traits, within the charactertype there is an array of character_traits correlated
 * To each enemy in the array
 * Each enemy also has an object within it, so an objecttype is also stored inside of it
 */
CharacterType * New_CharacterType(ObjectType *ot, BehaviorFunction behavior, int HP, int actionCost, int actionRegen) {
	CharacterType *ret = malloc(sizeof(CharacterType));
	/* Checks if your malloc failed */
	if (!ret) {
		fprintf(stderr, "Error creating CharacterType\n");
		return NULL;
	}

	/* Copy the passed values */
	ret->object_type = ot;
	ret->behavior = behavior;
	ret->defaultHP = HP;
	ret->defaultactionCost = actionCost;
	ret->defaultactionRegen = actionRegen;

	/* Create room for one character trait - increased when added */
	ret->character_traits = malloc(1 * sizeof(CharacterTraits));
	ret->character_traits_count = 0;
	ret->character_traits_size = 1;
	/* There's not much to do here, most of everything is in the ObjectType */
	return ret;
}

/* Destroy a CharacterType and each instance */
void Destroy_CharacterType(CharacterType *ct) {
	/* Frees the character_traits array */
	free(ct->character_traits);

	/* This will take care of everything else */
	Destroy_ObjectType(ct->object_type);
	ct = NULL;
}

/* Adds a character to a CharacterType Array */
void CharacterType_AddCharacter(CharacterType *ct, int x, int y) {
	//debug_msg("Added character to CharacterType at %p, count: %d\n", ct, ct->character_traits_count + 1);
	/* Adds an object that is correlated to a character */
	ObjectType_AddObject(ct->object_type, x, y);
	ct->character_traits_count = ct->object_type->instance_count;
	/* Reallocs the array if you need more space for more enemies */
	if (ct->character_traits_count == ct->character_traits_size) {
		ct->character_traits = realloc(ct->character_traits,
			2 * ct->character_traits_size * sizeof(CharacterTraits));
		ct->character_traits_size *= 2;
	}
	/* Sets all of the defaults for a charactertype */
	int temp = ct->character_traits_count;
	ct->object_type->instances[ct->character_traits_count - 1].animation = 0;
	ct->object_type->instances[ct->character_traits_count - 1].lastAnimation = 0;
	ct->character_traits[ct->character_traits_count - 1].hitDelta = 0;
	ct->character_traits[ct->character_traits_count - 1].is_dead = false;
	ct->character_traits[ct->character_traits_count - 1].is_on_floor = false;
	ct->character_traits[ct->character_traits_count - 1].is_hit = false;
	ct->character_traits[ct->character_traits_count - 1].is_attacking = false;
	ct->character_traits[ct->character_traits_count - 1].hitpoints = ct->defaultHP;
	ct->character_traits[ct->character_traits_count - 1].actionCost = ct->defaultactionCost;
	ct->character_traits[ct->character_traits_count - 1].actionRegen = ct->defaultactionRegen;
	ct->character_traits[ct->character_traits_count - 1].numActions = 100;
	
	/* Increments the size of the CharacterType */
}

/* Takes the charactertype and an index, and updates the character at that position */
void CharacterType_UpdateCharacter(CharacterType *ct, int instance_index, unsigned int dt, void *p) {
	/* ch_object is the physical object of the character instance */
	Object *ch_object = ct->object_type->instances + instance_index;
	/* ch_traits are the traits of the character instance */
	CharacterTraits *ch_traits = &ct->character_traits[instance_index];

	/* Cap velocities at +-5 */
	if (ch_traits->velocity.x > 5) {
		ch_traits->velocity.x = 5;
	}
	if (ch_traits->velocity.y > 5) {
		ch_traits->velocity.y = 5;
	}
	if (ch_traits->velocity.x < -5) {
		ch_traits->velocity.x = -5;
	}
	if (ch_traits->velocity.y < -5) {
		ch_traits->velocity.y = -5;
	}


	/* Apply velocities to the position */
	ch_object->dstrect.x += ch_traits->velocity.x;
	ch_object->dstrect.y += ch_traits->velocity.y;
	/* Ties the hitboxes to the dstrect */
	CharacterType_AdjustHitboxes(ct, instance_index);
}


/* Whenever an characters's dstrect moves, you have to move the hitboxes along with it
   This ties the hitboxes to the character's dstrect properly */
void CharacterType_AdjustHitboxes(CharacterType *ct, int instance_index) {
	//Shortcuts to hitboxes and dstrect
	SDL_Rect * hitboxes = ct->object_type->instances[instance_index].hitboxes;
	SDL_Rect * dstrect = &ct->object_type->instances[instance_index].dstrect;
	
	//Sets the top hitbox
	hitboxes[TOP_HITBOX].x = dstrect->x;
	hitboxes[TOP_HITBOX].y = dstrect->y;
	
	//Bottom
	hitboxes[BOTTOM_HITBOX].x = dstrect->x;
	hitboxes[BOTTOM_HITBOX].y = dstrect->y + ct->object_type->size.h - 8;
	
	//Etc
	hitboxes[LEFT_HITBOX].x = dstrect->x;
	hitboxes[LEFT_HITBOX].y = dstrect->y + 8;

	hitboxes[RIGHT_HITBOX].x = dstrect->x + ct->object_type->size.w - 8;
	hitboxes[RIGHT_HITBOX].y = dstrect->y + 8;
}

/* 
 * A bunch of checks for if the animation should move forward or not for the current index of the charactertype array 
 * Basically, it checks if you have changed animations in the last frame, because if you have you need to reset the delay
 * Between animations since you need a new delay
 * You also set the sprite indexes of all of the other animations back to zero, so that when you call upon them again they
 * Are back to 0
 */
void CharacterType_AnimateCharacter(CharacterType *ct, int ii, int animation, unsigned int *delay, unsigned int duration) {
	//Shortcut to object
	Object *object = ct->object_type->instances + ii;
	//Checks if animation has changed, if it has resets everything
	if (object->lastAnimation != animation) {
		object->lastAnimation = animation;
		*delay = 0;
		ObjectType_ResetSpriteIndexes(ct->object_type, ii, animation);
	}
	
	//Moves the animation forward to the next frame if you have been doing that animation for long enough
	if (*delay >= duration) {
		ObjectType_ObjectNextSprite(ct->object_type, ii);
		*delay = 0;
	}
}
