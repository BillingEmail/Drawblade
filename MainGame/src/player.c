#include <stdlib.h>
#define MAINGAME
#include "../include/player.h"
#include <math.h>
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
	ret->traits = ret->ctype->character_traits;

	ret->traits->velocity.y = 0;
	ret->traits->velocity.x = 0;

	return ret;
}

void Destroy_Player(Player *p) {
	/* Destroy everything below player */
	Destroy_CharacterType(p->ctype);
	free(p);
	p = NULL;
}

void Player_Render(Player *p, unsigned int dt, Container *c) {
	static unsigned int delay = 0;
	delay += dt;
	switch (p->object->animation) {
		case RUN_LEFT:
			CharacterType_AnimateCharacter(p->ctype, 0, RUN_LEFT, &delay, 100);
			if (fabs(p->traits->velocity.x) < .5) {
				p->object->sprite_index[RUN_LEFT] = 3;
			} else if (p->object->sprite_index[RUN_LEFT] > 7) {
				p->object->sprite_index[RUN_LEFT] = 0;
			}
			p->object->sprite_index[RUN_RIGHT] = p->object->sprite_index[RUN_LEFT];
		break;
		case RUN_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, RUN_RIGHT, &delay, 100);
			if (fabs(p->traits->velocity.x) < .5) {
				p->object->sprite_index[RUN_RIGHT] = 3;
			} else	if (p->object->sprite_index[RUN_RIGHT] > 7) {
				p->object->sprite_index[RUN_RIGHT] = 0;
			}
			p->object->sprite_index[RUN_LEFT] = p->object->sprite_index[RUN_RIGHT];
		break;
		case JUMP_LEFT:
			CharacterType_AnimateCharacter(p->ctype, 0, JUMP_LEFT, &delay, 50);
			if (p->object->sprite_index[JUMP_LEFT] > 3) {
				p->object->sprite_index[JUMP_LEFT] = 3;
			}
			p->object->sprite_index[JUMP_RIGHT] = p->object->sprite_index[JUMP_LEFT];
		case JUMP_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, JUMP_RIGHT, &delay, 50);
			if (p->object->sprite_index[JUMP_RIGHT] > 3) {
				p->object->sprite_index[JUMP_RIGHT] = 3;
			}
			p->object->sprite_index[JUMP_LEFT] = p->object->sprite_index[JUMP_RIGHT];
		break;

//		case ATTACK:
			/* attack lol TODO */
//		break;
//		case DEATH:
			/* die lol TODO render smoke thing lol */
//		break;
	}
	CharacterType_RenderCharacter(p->ctype, 0, dt, c);
}

/* Take input from wrapper and apply to the player */
void Player_Update(Player *p, unsigned int dt, Container *container) {

	/*TODO add default stand left/write */

	if (container->keyboardstate[SDL_SCANCODE_A]) {
		if (p->traits->is_on_floor) {
			ObjectType_SetObjectAnimation(p->otype, 0, RUN_LEFT);
		}
		p->traits->velocity.x -= 0.5;
		
	}

	if (container->keyboardstate[SDL_SCANCODE_D]) {
		if (p->traits->is_on_floor) {
			ObjectType_SetObjectAnimation(p->otype, 0, RUN_RIGHT);
		}
		p->traits->velocity.x += 0.5;
	}

	if (container->keyboardstate[SDL_SCANCODE_SPACE]) {
			if (p->object->animation == RUN_LEFT) {
				ObjectType_SetObjectAnimation(p->otype, 0, JUMP_LEFT);
			}

			if (p->object->animation == RUN_RIGHT) {
				ObjectType_SetObjectAnimation(p->otype, 0, JUMP_RIGHT);	
			}
		if (p->traits->is_on_floor) {
				p->traits->velocity.y = -7;
			p->traits->is_on_floor = false;
		}
	}


	p->traits->is_on_floor = false;
	/* cap velocities at 5 */
	if (p->traits->velocity.x > 5) {
		p->traits->velocity.x = 5;
	}
	if (p->traits->velocity.y > 7) {
		p->traits->velocity.y = 7;
	}
	if (p->traits->velocity.x < -5) {
		p->traits->velocity.x = -5;
	}
	if (p->traits->velocity.y < -7) {
		p->traits->velocity.y = -7;
	}


	p->traits->velocity.y += .25;

	p->traits->velocity.x *= 0.9;

	
	if (fabs(p->traits->velocity.x) < 0.1) p->traits->velocity.x = 0;

	p->object->dstrect.x += p->traits->velocity.x;
	p->object->dstrect.y += p->traits->velocity.y;		


	CharacterType_AdjustHitboxes(p->ctype, 0);


//	printf("dstrect <%d,%d>\ntop hitbox <%d,%d>\n", p->object->dstrect.x, p->object->dstrect.y,
//	p->object->hitboxes[TOP_HITBOX].x, p->object->hitboxes[TOP_HITBOX].y);
}

void Container_PlayerUpdateCamera(Container *container, Player *p) {
	container->camera->x = p->object->dstrect.x - container->camera->w / 2;
	container->camera->y = p->object->dstrect.y - container->camera->h / 2;
}
