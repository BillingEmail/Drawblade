/* character.h - type definition for CharacterType and CHaracter
 *
 * Characters work very similarly to objects, and are really just
 * one level higher than them - they are simply objects that also move.
 * CharacterTypes are made, and they essentially have an ObjectType,
 * and traits specific to the character, such as if they are affected
 * by gravity.
 */

#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"

/* Traits unique to characters */
typedef struct _character_traits {
	struct {
		int x;
		int y;
	} velocity;
} CharacterTraits;

typedef struct _charactertype {
	ObjectType *object_type; /* The ObjectType used for the CharacterType */

	CharacterTraits *character_traits; /* Array of character traits for each
	                                    *character of the type */

	bool affected_by_gravity; /* Whether or not the type is affected by gravity */

} CharacterType;

/* Create a new character type from an ObjectType and whether or not it falls */
CharacterType * New_CharacterType(ObjectType *ot, bool affected_by_gravity);

/* Destroy a charactertype, including it's objecttype etc */
void Destroy_CharacterType(CharacterType *t);

/* Render a specific instance of a CharacterType */
#define CharacterType_RenderCharacter(CT, R, II, C) ObjectType_RenderObject((CT)->object_type, (R), (II), (C))

/* Add another instance of the CharacterType to the list of instances */
#define CharacterType_AddCharacter(CT, X, Y, DA, DS) \
	ObjectType_AddObject((CT)->object_type, (X), (Y), (DA), (DS))

/* Returns the count of instances of a character type */
#define CharacterType_Count(CT) ObjectType_Count((CT)->object_type)

/* Kill a character - play it's death animation and destroy the instance */
void CharacterType_KillCharacter(CharacterType *ct, int instance_index);

/* Move a character with the keyboard - temporary */
void CharacterType_MoveCharacter(CharacterType *ct, int instance_index, const uint8_t *KeyboardState);

/* Update a character - temporary */
void CharacterType_UpdateCharacter(CharacterType *ct, int instance_index, int frame);

#endif
