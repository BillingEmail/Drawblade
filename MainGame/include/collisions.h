#ifndef collisions_h
#define collisions_h

#include <SDL2/SDL.h>

#include "../include/world.h"
#include "../include/player.h"
#include "../include/character.h"

void World_RunCollisions(World *world, Player *player);
void checkNormalCollision(CharacterType *charactertype, int instance_index, SDL_Rect *block);
int WhichRect(SDL_Rect *hitboxes, SDL_Rect *block);
void checkEnemyCollision(Player *player, SDL_Rect *enemy);

#endif
