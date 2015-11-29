#ifndef PLAYER_H
#define PLAYER_H

#include "../../shared/include/container.h" 
#include "character.h"
#include "object.h"

enum {
	RUN_RIGHT = 0,
	RUN_LEFT = 1,
	JUMP_RIGHT = 2,
	JUMP_LEFT = 3,
	ATTACK_RIGHT = 4,
	ATTACK_LEFT = 5, 
	HIT_RIGHT = 6,
	HIT_LEFT = 7
};

/* we'll make a player type later with weapon etc */
typedef struct _player {
	CharacterType *ctype; /* the actual type */

	/* just shortcuts */
	ObjectType *otype; /* may be handy */
	Object *object; /* shortcut to physical object */
	CharacterTraits *traits; /* shortcut to the traits */

	int numActions;
} Player;



/* Basically call New_CharacterType and do some things */
Player * New_Player(ObjectType *ot, int x, int y);

/* " */
void Destroy_Player(Player *p);

/* going to be a different function that renders the weapon as well lol */
//#define Player_Render(P, C) CharacterType_RenderCharacter((P)->ctype, 0, C)
void Player_Render(Player *p, unsigned int dt, Container *c);

/* update player using keyboard */
void Player_Update(Player *p, unsigned int dt, Container *c);

void Player_Attack(Player *p, Container *c);

/* Call CharacterType_KillCharacter() and end the game :^) */
void Player_Die(Player *p);

void Container_PlayerUpdateCamera(Container *c, Player *p);

#endif
