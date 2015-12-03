/* collisions.h - Finding collisions and adjusting the colliding objects
 *
 * Author: Satya Patel
 */

#ifndef collisions_h
#define collisions_h

#include <SDL2/SDL.h>

#include "../include/world.h"
#include "../include/player.h"
#include "../include/character.h"

/* Functions that run collisions on the whole world */

//loops through all objects and checks collisions
void World_RunCollisions(World *world);
//Just resets positions, does not stun the player or take away hp
void checkNormalCollision(CharacterType *charactertype, int instance_index, SDL_Rect *block);
//Tells you where the first character was hit from
int WhichRect(SDL_Rect *hitboxes, SDL_Rect *block);
//Does collision with damage involved
void checkEnemyCollision(Player *player, SDL_Rect *enemy);

#endif
