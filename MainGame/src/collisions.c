#include "../include/collisions.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/character.h"
#include <SDL2/SDL.h>

void World_RunCollisions(World *world) {
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
			checkNormalCollision(world->player->ctype, 0, &world->ObjectTypes[i]->instances[j].dstrect);
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
	SDL_Rect *dstrect = &charactertype->object_type->instances[instance_index].dstrect;
	CharacterTraits *accvel = charactertype->character_traits + instance_index;
	SDL_Rect *hitboxes = charactertype->object_type->instances[instance_index].hitboxes;

	for (int i = 0; i < 4; i++) {
		if (SDL_HasIntersection(hitboxes + i, block) == SDL_TRUE) {
			switch (i) {
				case TOP_HITBOX:
					puts("top");
					dstrect->y = block->y + block->h;
					accvel->acceleration.y = accvel->velocity.y = 0;
				break;
				case BOTTOM_HITBOX:
					puts("bottom");
					dstrect->y = block->y - dstrect->h;
					accvel->acceleration.y = accvel->velocity.y = 0;
					accvel->is_on_floor = true;
				break;
				case LEFT_HITBOX:
					puts("left");
					dstrect->x = block->x + block->w;
					accvel->acceleration.x = accvel->velocity.x = 0;
				break;
				case RIGHT_HITBOX:
					puts("right");
					dstrect->x = block->x - dstrect->w;
					accvel->acceleration.x = accvel->velocity.x = 0;	
				break;
			}
			CharacterType_AdjustHitboxes(charactertype, instance_index);
		}
	}
}
