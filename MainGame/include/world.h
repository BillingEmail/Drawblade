/* world.h - type definition for a World
 *
 * A world is just a list of objects/characters
 * for now.
 */
#ifndef world_h
#define world_h
#include "character.h"
#include "../../shared/include/level.h"

enum {
	OBJECT_BRICK = 0,
}

enum {
	ENEMY_1 = 0,
	ENEMY_2 = 1,
	ENEMY_3 = 2
}

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

/* Update the world */
void World_Update(World *w, Player *p);

/* Load a world from a file */
World * NewWorld_FromFile(char *path);

/* Destroy a world */
void Destroy_World(World *w);

/* Render all of the facets of the world */
void World_Render(World *w, int frame, Container *c);

#endif
