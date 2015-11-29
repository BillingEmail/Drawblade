#include <stdlib.h>
#define MAINGAME
#include "../include/player.h"
#include <math.h>
#include "../include/behavior.h"
#include "../include/character.h"
#include "../../shared/include/container.h"

/* Create the player */
Player * New_Player(ObjectType *ot, int x, int y, LevelType theme) {
	Player *ret = malloc(sizeof(Player));
	ret->theme = theme;

	ret->ctype = New_CharacterType(ot, NULL, 5, 100, 10);
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
			if (p->object->sprite_index[RUN_LEFT] > 7) {
				p->object->sprite_index[RUN_LEFT] = 0;
			}
			p->object->sprite_index[RUN_RIGHT] = p->object->sprite_index[RUN_LEFT];
		break;
		case RUN_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, RUN_RIGHT, &delay, 100);
			if (p->object->sprite_index[RUN_RIGHT] > 7) {
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
			if (p->object->sprite_index[JUMP_RIGHT] > 2) {
				p->object->sprite_index[JUMP_RIGHT] = 2;
			}
			p->object->sprite_index[JUMP_LEFT] = p->object->sprite_index[JUMP_RIGHT];
		break;
		case ATTACK_LEFT:
			CharacterType_AnimateCharacter(p->ctype, 0, ATTACK_LEFT, &delay, 50);
			if (p->object->sprite_index[ATTACK_LEFT] > 3) {
				p->traits->is_attacking = false;
				p->object->sprite_index[ATTACK_LEFT] = 3; 
			}
			p->object->sprite_index[ATTACK_RIGHT] = p->object->sprite_index[ATTACK_LEFT];
		break;
		case ATTACK_RIGHT:
			CharacterType_AnimateCharacter(p->ctype, 0, ATTACK_RIGHT, &delay, 50);
			if (p->object->sprite_index[ATTACK_RIGHT] > 3) {
				p->traits->is_attacking = false;
				p->object->sprite_index[ATTACK_RIGHT] = 3;
			}
			p->object->sprite_index[ATTACK_LEFT] = p->object->sprite_index[ATTACK_RIGHT];
		break;
		case STAND_RIGHT:
			ObjectType_SetObjectAnimation(p->otype, 0, STAND_RIGHT);
		break;
		case STAND_LEFT:
			ObjectType_SetObjectAnimation(p->otype, 0, STAND_LEFT);
		break;
	}

	CharacterType_RenderCharacter(p->ctype, 0, dt, c);
	p->object->lastAnimation = p->object->animation;
}

/* Take input from wrapper and apply to the player */
void Player_Update(Player *p, unsigned int dt, Container *container) {
	/* Checks whether the last sprite was facing left or right */
	bool facingLeft = (p->object->lastAnimation % 2 == 1);
	if (!p->traits->is_hit && !p->traits->is_dead) {
	
		if (facingLeft) {
			ObjectType_SetObjectAnimation(p->otype, 0, STAND_LEFT);
		}
		if (!facingLeft) {
			ObjectType_SetObjectAnimation(p->otype, 0, STAND_RIGHT);
		}

		if (container->keyboardstate[SDL_SCANCODE_A]) {
				ObjectType_SetObjectAnimation(p->otype, 0, RUN_LEFT);
			p->traits->velocity.x -= 0.5;
		
		}

		if (container->keyboardstate[SDL_SCANCODE_D]) {
				ObjectType_SetObjectAnimation(p->otype, 0, RUN_RIGHT);
			p->traits->velocity.x += 0.5;
		}

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

		if (container->mouse.leftClick) {
<<<<<<< HEAD
			if (p->traits->canAttack) {
=======
			if (p->traits->numActions > p->traits->actionCost && !p->traits->is_attacking) {
>>>>>>> 4f4f813d9e1cc1872cec2455ddd958afb5fd1a0d
				if(container->mouse.x <= p->object->dstrect.x + p->object->dstrect.w - container->camera->x) {
					ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_LEFT);
				}
				else {
					ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_RIGHT);
				}

				Player_Attack(p, container);
			}
		}

		if (p->traits->is_attacking) {
			if(p->object->lastAnimation == ATTACK_LEFT) {
				ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_LEFT);
			}
			if(p->object->lastAnimation == ATTACK_RIGHT) {
				ObjectType_SetObjectAnimation(p->otype, 0, ATTACK_RIGHT);
			}
			Player_Attack(p, container);
		}

	}

	if (p->traits->is_hit) {
		if (p->traits->velocity.x > 0) {
			ObjectType_SetObjectAnimation(p->otype, 0, HIT_LEFT);
		}
		else {
			ObjectType_SetObjectAnimation(p->otype, 0, HIT_RIGHT);
		}
	}

	
	p->traits->numActions += p->traits->actionRegen;
	if (p->traits->numActions > 100) p->traits->numActions = 100;

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

	p->traits->velocity.y += .20;
	p->traits->velocity.x *= 0.9;

	
	if (fabs(p->traits->velocity.x) < 0.3) p->traits->velocity.x = 0;

	p->object->dstrect.x += ceil(p->traits->velocity.x);
	p->object->dstrect.y += ceil(p->traits->velocity.y);	

	p->traits->hitDelta -= dt;

	if (p->traits->hitDelta < 0) {
		p->traits->is_hit = false;
	}

	CharacterType_AdjustHitboxes(p->ctype, 0);
}

void Player_Attack(Player *p, Container *c) { 
 	if (!p->traits->is_attacking) {
		p->traits->numActions -= p->traits->actionCost;
	}
	p->traits->is_attacking = true;
}

void Container_PlayerUpdateCamera(Container *container, Player *p) {
	container->camera->x = p->object->dstrect.x - container->camera->w / 2;
	container->camera->y = p->object->dstrect.y - container->camera->h / 2;
}
