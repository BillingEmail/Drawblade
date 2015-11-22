#include <stdlib.h>
#define MAINGAME
#include "../include/player.h"
#include "../include/behavior.h"
#include "../include/character.h"
#include "../../shared/include/container.h"

/* Create the player */
Player * New_Player(ObjectType *ot, int x, int y) {
	Player *ret = malloc(sizeof(Player));

	ret->ctype = New_CharacterType(ot, NULL);
	/* Add the player character */
	CharacterType_AddCharacter(ret->ctype, x, y, 0, 0);
	/* shortcut to the objecttype, not sure why */
	ret->otype = ret->ctype->object_type;
	/* shortcut to the physical object */
	ret->object = ret->otype->instances;

	return ret;
}

void Destroy_Player(Player *p) {
	/* Destroy everything below player */
	Destroy_CharacterType(p->ctype);
	free(p);
	p = NULL;
}

/* Take input from wrapper and apply to the player */
void Player_Update(Player *p, Container *container) {
	/* Jump */
	if (container->keyboardstate[SDL_SCANCODE_SPACE]) {
		if (p->traits->velocity.y == 0) {
			p->traits->velocity.y = -5;
		}
	}
	/* fastfall */
	if (!p->traits->is_on_floor && container->keyboardstate[SDL_SCANCODE_S]) {
		p->traits->velocity.y += 2;
	}
	/* left */
	if (container->keyboardstate[SDL_SCANCODE_A]) {
		p->traits->velocity.x -= 2;
	}
	/* right */
	if (container->keyboardstate[SDL_SCANCODE_D]) {
		p->traits->velocity.y += 2;
	}
	
	/* cap velocities at 5 */
	if (p->traits->velocity.x > 5) {
		p->traits->velocity.x = 5;
	}
	if (p->traits->velocity.y > 5) {
		p->traits->velocity.y = 5;
	}
	if (p->traits->velocity.x < -5) {
		p->traits->velocity.x = -5;
	}
	if (p->traits->velocity.y < -5) {
		p->traits->velocity.y = 5;
	}		
}
