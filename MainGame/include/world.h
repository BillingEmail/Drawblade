/* world.h - type definition for a World
 *
 * A world is just a list of objects/characters
 * for now.
 */
#ifndef world_h
#define world_h
#include "character.h"


/* List of characters and objects -- remember that each type also has a list
 * instances of that type
 */
typedef struct _world {
	struct {
		int w;
		int h;
	} size; /* The size of the world in pixels */
	PlayerType* Playertype; /* The Playertype */
	CharacterType* Enemytypes;
	ObjectType* Objecttypes;
	int Enemycount; /* Count of how many ^ */
	int Objectcount;
	Texture *background; /* Texture used for the background for the world */
} World;

/* Update the world */
void World_Update(World *w);

/* Load a world from a file */
World * NewWorld_FromFile(char *path);

/* Destroy a world */
void Destroy_World(World *w);

/* Update all of the facets in a world */
void World_Update(World *w);

/* Render all of the facets of the world */
void World_Render(World *w, int frame, SDL_Renderer, *r SDL_Rect *Camera);
#endif
