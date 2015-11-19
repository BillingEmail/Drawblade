#ifndef PLAYER_H
#define PLAYER_H

#include "../../shared/include/SDLhelpers.h" 

typedef enum {
	SWORD, BOW, STAFF
} Weapontype;

typedef struct _weapon {
	CharacterType *projectile; /* null if sword */
	CharacterType *weapon; /* the weapon, always index 0 */
	WeaponType type;
} Weapon;

/* we'll make a player type later with weapon etc */
typedef struct _player {
	CharacterType *ctype; /* the actual type */

	/* just shortcuts */
	ObjectType *otype; /* may be handy */
	Object *object; /* shortcut to physical object */
	CharacterTraits *traits; /* shortcut to the traits */

	Weapon *weapon; /* Array of 3 weapons */
	WeaponType currentWeapon; /* current weapon :^) so like player->weapon[currentWeapon] etc */
} Player;

/* Basically call New_CharacterType and do some things */
Player * New_Player(ObjectType *ot, int x, int y);

/* " */
void Destroy_Player(Player *p);

/* going to be a different function that renders the weapon as well lol */
#define Player_Render(P, SDLW) CharacterType_RenderCharacter((P)->ctype, 0, (SDLW))

/* update player using keyboard */
void Player_Update(Player *p, SDLWrapper *w);

/* Call CharacterType_KillCharacter() and end the game :^) */
void Player_Die(Player *p);

#endif
