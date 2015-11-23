#include "../include/collisions.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/character.h"
#include <SDL2/SDL.h>

void World_RunCollisions(World *world, Player *player) {
/*	for (int i = 0; i < world->EnemyTypeCount; i++) {
		for (int j = 0; j < world->EnemyTypes->instance_count; j++) {
			checkDmgCollision(//Player, //Enemy);
		}

	}
*/
	/* This nasty loop checks each object's collision 
	with each character and player, and also adjusts hitboxes
	if there is a collision to its previous position
	 */

	for (int i = 0; i < world->ObjectTypeCount; i++) {
		for (int j = 0; j < world->ObjectTypes[i]->instance_count; j++) {
			//Player collision
			checkNormalCollision(player->ctype, 0, &world->ObjectTypes[i]->instances[j].dstrect);
			//For each enemy check collision with each block
			for (int k = 0; k < world->EnemyTypeCount; k++) {
				for (int l = 0; l < world->EnemyTypes[k]->object_type->instance_count; l++) {
					checkNormalCollision(world->EnemyTypes[k], l, &world->ObjectTypes[i]->instances[j].dstrect);
				}
			}
		}
	}
}

void checkNormalCollision(CharacterType *charactertype, int instance_index, SDL_Rect *block) {
	int collRect = WhichRect(charactertype->object_type->instances[instance_index].hitboxes, block);
	SDL_Rect *dstrect = &charactertype->object_type->instances[instance_index].dstrect;
	CharacterTraits *accvel = charactertype->character_traits + instance_index;
	switch (collRect) {
		case TOP_HITBOX:
			dstrect->y = block->y + block->h;
		break;
		case BOTTOM_HITBOX:
			dstrect->y = block->y;
		break;
		case LEFT_HITBOX:
			dstrect->x = block->x + block->w;
		break;
		case RIGHT_HITBOX:
			dstrect->x = block->x;
		break;
	}

	if (collRect == TOP_HITBOX || collRect == BOTTOM_HITBOX) {
		accvel->acceleration.y = accvel->velocity.y = 0;
	}
	if (collRect == LEFT_HITBOX || collRect == RIGHT_HITBOX) {
		accvel->acceleration.x = accvel->velocity.x = 0;
	}
}


int WhichRect(SDL_Rect *hitboxes, SDL_Rect *block) {
	for (int i = 0; i < 4; i++) {
		if (SDL_IntersectRect(hitboxes, block, NULL)) {
			return i;
		}
	}
	return 0;
}
