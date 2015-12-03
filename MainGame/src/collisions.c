/* collisions.c - Finding collisions and adjusting objects accordingly
 *
 * Author: Satya Patel
 */

#include "../include/collisions.h"
#include "../include/player.h"
#include "../include/object.h"
#include "../include/character.h"
#include <SDL2/SDL.h>


/* Runs all of the collisions in the world by checking all useful combinations of objects
 * to see if they are colliding.  This means it checks for all collisions between players.
 * enemies, etc. with bricks, players and enemies, etc., but not between brick and brick
 * Since bricks can't collide if they don't move
 */
void World_RunCollisions(World *world) {
	//This would be for checking if the player collided for an enemy, but it is not used
/*	for (int i = 0; i < world->EnemyTypeCount; i++) {
		for (int j = 0; j < world->EnemyTypes->instance_count; j++) {
			checkDmgCollision(//Player, //Enemy);
		}

	}
*/	


	/* This loop checks each object's collision with each character and player*/

	for (int i = 0; i < world->ObjectTypeCount; i++) {
		for (int j = 0; j < world->ObjectTypes[i]->instance_count; j++) {
			//Player collision
			checkNormalCollision(world->player->ctype, 0, &world->ObjectTypes[i]->instances[j].dstrect);
			//For each enemy check collision with each block
/*			for (int k = 0; k < world->EnemyTypeCount; k++) {
				for (int l = 0; l < world->EnemyTypes[k]->object_type->instance_count; l++) {
					checkNormalCollision(world->EnemyTypes[k], l, &world->ObjectTypes[i]->instances[j].dstrect);
				}
			}
*/		}
	}
/* Checks if the player has collided with the goalpost at the end of the level */
	for (int i = 0; i < world->goalpost->instance_count; i++) {
		for (int j = 0; j < 4; j++) {
			/* If a player's hitbox intersects the goalpost */
			if (SDL_HasIntersection(world->player->object->hitboxes + j, &world->goalpost->instances[i].dstrect)) {
				world->is_complete = true;
				return;
			}
		}
	}
}
/* Normal collision implies that neither of the objects taking part in the collision take dmg 
 * This collision is tested by checking each one of the first object's hitboxes, and if any of
 * them are colliding, then it moves the first object out of the second object
 */
void checkNormalCollision(CharacterType *charactertype, int instance_index, SDL_Rect *block) {
	SDL_Rect *dstrect = &charactertype->object_type->instances[instance_index].dstrect;
	CharacterTraits *accvel = charactertype->character_traits + instance_index;
	SDL_Rect *hitboxes = charactertype->object_type->instances[instance_index].hitboxes;
	/* Loops through all hitboxes */
	for (int i = 0; i < 4; i++) {
		//If a block is intersecting
		if (SDL_HasIntersection(hitboxes + i, block) == SDL_TRUE) {
			switch (i) {
				//Checks which blocks are intersecting and adjusts accordingly
				case TOP_HITBOX:
					dstrect->y = block->y + block->h;
					accvel->acceleration.y = accvel->velocity.y = 0;
				break;
				case BOTTOM_HITBOX:
					dstrect->y = block->y - dstrect->h;
					accvel->acceleration.y = accvel->velocity.y = 0;
					//Also sets is_on_floor to true so that we know we are on a block
					//Is important for checking for animations/etc.
					accvel->is_on_floor = true;
				break;
				case LEFT_HITBOX:
					dstrect->x = block->x + block->w;
					accvel->acceleration.x = accvel->velocity.x = 0;
				break;
				case RIGHT_HITBOX:
					dstrect->x = block->x - dstrect->w;
					accvel->acceleration.x = accvel->velocity.x = 0;	
				break;
			}
			//Adjusts your hitboxes to your new dstrect position
			CharacterType_AdjustHitboxes(charactertype, instance_index);
		}
	}
}
/* Ya we don't have enemies lol */
void checkEnemyCollision(Player *p, SDL_Rect *block) {
		 /* TODO */
}
