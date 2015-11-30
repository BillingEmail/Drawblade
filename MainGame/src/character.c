/* character.c - Implementation for CharacterType
 *
 * See character.h for details
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/character.h"
#include "../include/object.h"
#include "../include/behavior.h"
#include "../../shared/include/container.h"

/* Create a new CharacterType */
CharacterType * New_CharacterType(ObjectType *ot, void (*behavior)(struct _charactertype *self, int, struct _charactertype *, int), int HP, int actionCost, int actionRegen) {
	CharacterType *ret = malloc(sizeof(CharacterType));
	if (!ret) {
		fprintf(stderr, "Error creating CharacterType\n");
		return NULL;
	}

	/* Copy the passed values */
	ret->object_type = ot;
	ret->behavior = behavior;

	/* Create room for one character trait - increased when added */
	ret->character_traits = malloc(2 * sizeof(CharacterTraits));
	ret->character_traits_count = 0;
	ret->character_traits_size = 2;
	ret->defaultHP = HP;
	ret->defaultactionCost = actionCost;
	ret->defaultactionRegen = actionRegen;
	/* There's not much to do here, most of everything is in the ObjectType */
	return ret;
}

/* Destroy a CharacterType and each instance */
void Destroy_CharacterType(CharacterType *ct) {
	/* The only dynamically allocated aspect of CharacterType is the list of traits */
	int i;
	for (i = 0; i < ct->object_type->instance_count; i++) {
		free(ct->character_traits);
	}
	/* This will take care of everything else */
	Destroy_ObjectType(ct->object_type);

	ct = NULL;
}

/* testing */
void CharacterType_AddCharacter(CharacterType *ct, int x, int y) {
	ObjectType_AddObject(ct->object_type, x, y);

	/* losing my patience with commenting rn tbh */
	if (ct->character_traits_count == ct->character_traits_size) {
		ct->character_traits = realloc(ct->character_traits,
			2 * ct->character_traits_size * sizeof(CharacterTraits));
		ct->character_traits_size *= 2;
	}

	ct->object_type->instances[ct->character_traits_count].animation = 0;
	ct->object_type->instances[ct->character_traits_count].lastAnimation = 0;

	ct->character_traits[ct->character_traits_count].hitDelta = 0;
	ct->character_traits[ct->character_traits_count].is_dead = false;
	ct->character_traits[ct->character_traits_count].is_on_floor = false;
	ct->character_traits[ct->character_traits_count].is_hit = false;
	ct->character_traits[ct->character_traits_count].is_attacking = false;
	ct->character_traits[ct->character_traits_count].hitpoints = ct->defaultHP;
	ct->character_traits[ct->character_traits_count].actionCost = ct->defaultactionCost;
	ct->character_traits[ct->character_traits_count].actionRegen = ct->defaultactionRegen;
	ct->character_traits[ct->character_traits_count].numActions = 100;
	ct->character_traits_count++;
}


void CharacterType_UpdateCharacter(CharacterType *ct, int instance_index, unsigned int dt) {
	/* ch_object is the physical object of the character instance */
	Object *ch_object = ct->object_type->instances + instance_index;
	/* ch_traits are the traits of the character instance */
//	CharacterTraits *ch_traits = &ct->character_traits[instance_index];


	printf("%d, %d\n", ch_object->animation, __LINE__);
	ch_object->animation = 1;	
	/* need to pass player to this -- playerType global? */
//	ct->behavior(ct, instance_index, NULL, 0);

	/* Cap velocities at +-5 */
//	if (ch_traits->velocity.x > 5) {
//		ch_traits->velocity.x = 5;
//	}
//	if (ch_traits->velocity.y > 5) {
//		ch_traits->velocity.y = 5;
//	}
//	if (ch_traits->velocity.x < -5) {
//		ch_traits->velocity.x = -5;
//	}
//	if (ch_traits->velocity.y < -5) {
//		ch_traits->velocity.y = -5;
//	}



	/* Apply velocities to the position */
//	ch_object->dstrect.x += ch_traits->velocity.x;
//	ch_object->dstrect.y += ch_traits->velocity.y;

//	CharacterType_AdjustHitboxes(ct, instance_index);
}

void CharacterType_AdjustHitboxes(CharacterType *ct, int instance_index) {
	SDL_Rect * hitboxes = ct->object_type->instances[instance_index].hitboxes;
	SDL_Rect * dstrect = &ct->object_type->instances[instance_index].dstrect;

	hitboxes[TOP_HITBOX].x = dstrect->x;
	hitboxes[TOP_HITBOX].y = dstrect->y;

	hitboxes[BOTTOM_HITBOX].x = dstrect->x;
	hitboxes[BOTTOM_HITBOX].y = dstrect->y + ct->object_type->size.h - 8;

	hitboxes[LEFT_HITBOX].x = dstrect->x;
	hitboxes[LEFT_HITBOX].y = dstrect->y + 8;

	hitboxes[RIGHT_HITBOX].x = dstrect->x + ct->object_type->size.w - 8;
	hitboxes[RIGHT_HITBOX].y = dstrect->y + 8;
}

void CharacterType_AnimateCharacter(CharacterType *ct, int ii, int animation, unsigned int *delay, unsigned int duration) {
	Object *object = ct->object_type->instances + ii;
	if (object->lastAnimation != animation) {
		object->lastAnimation = animation;
		*delay = 0;
		ObjectType_ResetSpriteIndexes(ct->object_type, ii, animation);
	}
	if (*delay >= duration) {
		ObjectType_ObjectNextSprite(ct->object_type, ii);
		*delay = 0;
	}
}
