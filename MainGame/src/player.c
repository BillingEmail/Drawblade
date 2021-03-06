/* player.c - functions specific to the player
 *
 * Authors: Satya Patel, Sean Rapp
 */


#include <stdlib.h>
#include "../include/player.h"
#include <math.h>
#include "../include/behavior.h"
#include "../include/character.h"
#include "../../shared/include/container.h"

/* Create the player */
Player * New_Player(ObjectType *ot, int x, int y, LevelType theme) {
	Player *ret = malloc(sizeof(Player));
	ret->theme = theme;

	ret->ctype = New_CharacterType(ot, NULL, 100000, 100, 5);
	/* Add the player character */
	CharacterType_AddCharacter(ret->ctype, x, y);
	/* shortcut to the objecttype, not sure why */
	ret->otype = ret->ctype->object_type;
	/* shortcut to the physical object */
	ret->object = ret->otype->instances;
	ret->traits = ret->ctype->character_traits;
	ret->traits->velocity.y = 0;
	ret->traits->velocity.x = 0;

	ret->traits->hitpoints = 200000;

	return ret;
}

/* Free the player */
void Destroy_Player(Player *p) {
	/* Destroy everything below player */
	Destroy_CharacterType(p->ctype);
	free(p);
	p = NULL;
}

/* Render the player */
void Player_Render(Player *p, unsigned int dt, Container *c) {
	static unsigned int delay = 0;
	delay += dt;

	/* Depending on which animation is set, animate the player accordingly */
	switch (p->object->animation) {
		case RUN_LEFT:
			CharacterType_AnimateCharacter(p->ctype, 0, RUN_LEFT, &delay, 100);
			/* Cycle through the sprites */
			if (p->object->sprite_index[RUN_LEFT] > 7) {
				p->object->sprite_index[RUN_LEFT] = 0;
			}
			p->object->sprite_index[RUN_RIGHT] = p->object->sprite_index[RUN_LEFT];
		break;
		case RUN_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, RUN_RIGHT, &delay, 100);
			/* Cyclle through the sprites */
			if (p->object->sprite_index[RUN_RIGHT] > 7) {
				p->object->sprite_index[RUN_RIGHT] = 0;
			}
			p->object->sprite_index[RUN_LEFT] = p->object->sprite_index[RUN_RIGHT];
		break;
		case JUMP_LEFT:
			CharacterType_AnimateCharacter(p->ctype, 0, JUMP_LEFT, &delay, 50);
			/* Animate to the fourth sprite then stop */
			if (p->object->sprite_index[JUMP_LEFT] > 3) {
				p->object->sprite_index[JUMP_LEFT] = 3;
			}
			p->object->sprite_index[JUMP_RIGHT] = p->object->sprite_index[JUMP_LEFT];
		case JUMP_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, JUMP_RIGHT, &delay, 50);
			/* Animate to the fourth sprite then stop */
			if (p->object->sprite_index[JUMP_RIGHT] > 3) {
				p->object->sprite_index[JUMP_RIGHT] = 3;
			}
			p->object->sprite_index[JUMP_LEFT] = p->object->sprite_index[JUMP_RIGHT];
		break;
		case ATTACK_LEFT:
			CharacterType_AnimateCharacter(p->ctype, 0, ATTACK_LEFT, &delay, 50);
			/* Stop attacking when you hit the final sprite */
			if (p->object->sprite_index[ATTACK_LEFT] > 2) {
				p->traits->is_attacking = false;
				p->object->sprite_index[ATTACK_LEFT] = 2; 
			}
			p->object->sprite_index[ATTACK_RIGHT] = p->object->sprite_index[ATTACK_LEFT];
		break;
		case ATTACK_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, ATTACK_RIGHT, &delay, 50);
			if (p->object->sprite_index[ATTACK_RIGHT] > 2) {
				p->traits->is_attacking = false;
				p->object->sprite_index[ATTACK_RIGHT] = 2;
			}
			p->object->sprite_index[ATTACK_LEFT] = p->object->sprite_index[ATTACK_RIGHT];
		break;
		case STAND_RIGHT:
		/* Just set it to the standing still animation in running */
			ObjectType_ResetSpriteIndexes(p->ctype->object_type, 0, STAND_RIGHT);
			ObjectType_SetObjectAnimation(p->otype, 0, RUN_RIGHT);
		break;
		case STAND_LEFT:
			ObjectType_ResetSpriteIndexes(p->ctype->object_type, 0, STAND_LEFT);
			ObjectType_SetObjectAnimation(p->otype, 0, RUN_LEFT);
		break;
	}

	CharacterType_RenderCharacter(p->ctype, 0, dt, c);
	p->object->lastAnimation = p->object->animation;
}

/* Take user input and apply to the player */
void Player_Update(Player *p, unsigned int dt, Container *container) {
	/* Checks whether the last sprite was facing left or right */
	bool facingLeft = (p->object->lastAnimation % 2 == 1);
	/* Only makes these checks if the player isnt hit or dead */
	if (!p->traits->is_hit && !p->traits->is_dead) {
	
		if (facingLeft) {
			ObjectType_SetObjectAnimation(p->otype, 0, STAND_LEFT);
		}
		if (!facingLeft) {
			ObjectType_SetObjectAnimation(p->otype, 0, STAND_RIGHT);
		}

		/* Move left */
		if (container->keyboardstate[SDL_SCANCODE_A]) {
				ObjectType_SetObjectAnimation(p->otype, 0, RUN_LEFT);
			p->traits->velocity.x -= 0.5;
		
		}
		/* Move right */
		if (container->keyboardstate[SDL_SCANCODE_D]) {
				ObjectType_SetObjectAnimation(p->otype, 0, RUN_RIGHT);
			p->traits->velocity.x += 0.5;
		}

		/* Jump */
		if (container->keyboardstate[SDL_SCANCODE_SPACE]) {
			if (p->traits->is_on_floor) {
				p->traits->velocity.y = -7;
				p->traits->is_on_floor = false;
			}
		}
	
		if (!p->traits->is_on_floor) {
			if (p->object->animation == RUN_LEFT || p->object->animation == STAND_LEFT) {
				ObjectType_SetObjectAnimation(p->otype, 0, JUMP_LEFT);
			}
			if (p->object->animation == RUN_RIGHT || p->object->animation == STAND_RIGHT) {
				ObjectType_SetObjectAnimation(p->otype, 0, JUMP_RIGHT);	
			}
	
		}
/*		** Not needed if doing just the runner with timed levels ***********
		if (container->mouse.leftClick) {

			if (p->traits->numActions >= p->traits->actionCost && !p->traits->is_attacking) {

				if(container->mouse.x <= p->object->dstrect.x + p->object->dstrect.w - container->camera->x) {
					ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_LEFT);
				}
				else {
					ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_RIGHT);
				}
				p->traits->numActions -= p->traits->actionCost;
				p->traits->is_attacking = true;
			}
		}

		if (p->traits->is_attacking) {
			if(p->object->lastAnimation == ATTACK_LEFT) {
				ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_LEFT);
			}
			if(p->object->lastAnimation == ATTACK_RIGHT) {
				ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_RIGHT);
			}
		}

	}

	if (p->traits->is_hit) {
		if (p->traits->velocity.x > 0) {
			ObjectType_SetObjectAnimation(p->otype, 0, HIT_LEFT);
		}
		else {
			ObjectType_SetObjectAnimation(p->otype, 0, HIT_RIGHT);
		}
*/	}

	/* Also not needed with the timer
	p->traits->numActions += p->traits->actionRegen;
	if (p->traits->numActions > 100) p->traits->numActions = 100;
	*/
	p->traits->is_on_floor = false;
	
	/* cap velocities */
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

	/* Gravity */
	p->traits->velocity.y += .20;
	/* Slow down after A or D key is released instead of stopping at once */
	p->traits->velocity.x *= 0.9;

	/* Set to 0 if nearly 0 */
	if (fabs(p->traits->velocity.x) < 0.3) p->traits->velocity.x = 0;

	/* Apply velocity */
	p->object->dstrect.x += ceil(p->traits->velocity.x);
	p->object->dstrect.y += ceil(p->traits->velocity.y);	

	/* Since the player is never hit, this is not needed
	p->traits->hitDelta -= dt;

	if (p->traits->hitDelta < 0) {
		p->traits->is_hit = false;
		p->traits->hitDelta = .75;
	}
	*/
	CharacterType_AdjustHitboxes(p->ctype, 0);
}

/* Move the character according to the player's position */
void Container_PlayerUpdateCamera(Container *container, Player *p) {
	container->camera->x = p->object->dstrect.x - container->camera->w / 2;
	container->camera->y = p->object->dstrect.y - container->camera->h / 2;
}
