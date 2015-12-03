/* world.h - type definition for a World
 *
 * The working environment of the running game.
 *
 * Authors: Sean Rapp, Satya Patel
 */
#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "character.h"
#include "../../shared/include/level.h"

//Defines all of the object types
enum {
	OBJECT_BRICK = 0,
};

//Defines all of the enemy types
enum {
	ENEMY_1 = 0,
	ENEMY_2 = 1,
	ENEMY_3 = 2
};;

/* List of characters and objects -- remember that each type also has a list
 * instances of that type
 */
typedef struct _world {
	struct {
		int w;
		int h;
	} size; /* The size of the world in pixels */

	Player *player;

	ObjectType *goalpost;

	CharacterType **EnemyTypes;

	ObjectType **ObjectTypes;

	int EnemyTypeCount; /* Count of how many types of enemies */

	int ObjectTypeCount; /* "                    " of Objects */

	struct {
		Texture *still;
		Texture *tiled;
	} background;

	bool is_complete; /* player -> goalpost :^) */

	LevelType theme; /* theme of level */

} World;

/* Create an actual world from a already-loaded level */
World * World_LoadWorldFromLevel(Level *level, Container *container);

/* Update the world */
void World_Update(World *w, unsigned int dt, Container *container);

/* Load a world from a file */
World * NewWorld_FromFile(const char *path, Container *c);

/* Each brick is given a certain look based on the bricks around it */
void World_SetBrickSprites(World *w, int instance);

/* Destroy a world */
void Destroy_World(World *w);

/* Render all of the facets of the world */
void World_Render(World *w, unsigned int dt, Container *c);

/* Cleans the world and frees resources */
void World_Destroy(World *w);

#endif
