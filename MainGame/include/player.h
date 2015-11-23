#ifndef PLAYER_H
#define PLAYER_H

#include "../../shared/include/container.h" 
#include "character.h"
#include "object.h"


/* we'll make a player type later with weapon etc */
typedef struct _player {
	CharacterType *ctype; /* the actual type */

	/* just shortcuts */
	ObjectType *otype; /* may be handy */
	Object *object; /* shortcut to physical object */
	CharacterTraits *traits; /* shortcut to the traits */

} Player;



/* we'll make a player type later with weapon etc */
//typedef struct _player {
//	CharacterType *ctype; /* the actual type */

	/* just shortcuts */
//	ObjectType *otype; /* may be handy */
//	Object *object; /* shortcut to physical object */
//	CharacterTraits *traits; /* shortcut to the traits */

//} Player;

/* Basically call New_CharacterType and do some things */
Player * New_Player(ObjectType *ot, int x, int y);

/* " */
void Destroy_Player(Player *p);

/* going to be a different function that renders the weapon as well lol */
#define Player_Render(P, C) CharacterType_RenderCharacter((P)->ctype, 0, C)

/* update player using keyboard */
void Player_Update(Player *p, Container *c);

/* Call CharacterType_KillCharacter() and end the game :^) */
void Player_Die(Player *p);

void Container_PlayerUpdateCamera(Container *c, Player *p);

#endif
