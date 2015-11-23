/* world.h - type definition for a World
 *
 * A world is just a list of objects/characters
 * for now.
 */
#ifndef WORLD_H
#define WORLD_H

#include "player.h"
#include "character.h"
#include "../../shared/include/level.h"

enum {
	OBJECT_BRICK = 0,
};

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

	CharacterType **EnemyTypes;

	ObjectType **ObjectTypes;

	int EnemyTypeCount; /* Count of how many types of enemies */

	int ObjectTypeCount; /* "                    " of Objects */

	Texture *background; /* Texture used for the background for the world */

	bool is_complete; /* player -> goalpost :^) */

	LevelType theme; /* theme of level */

} World;

/* Create an actual world from a already-loaded level */
World * World_LoadWorldFromLevel(Level *level, Player *p, Container *container);

/* Update the world */
void World_Update(World *w, Player *p, int frame);

/* Load a world from a file */
World * NewWorld_FromFile(char *path, Player *p, Container *c);

/* Destroy a world */
void Destroy_World(World *w);

/* Render all of the facets of the world */
void World_Render(World *w, int frame, Container *c);

void World_Destroy(World *w);

#endif
