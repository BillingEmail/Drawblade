/* world.h - type definition for a World
 *
 * A world is just a list of objects/characters
 * for now.
 */

#include "character.h"

typedef enum _co {CHARACTER, OBJECT} character_or_object;

/* Tagged union of either a character type or object type */
typedef struct _c_o_o {
	character_or_object type;
	union {
		CharacterType *ct;
		ObjectType *ot;
	};
} CharacterType_Or_ObjectType;

/* List of characters and objects -- remember that each type also has a list
 * instances of that type
 */
typedef struct _world {
	struct {
		int w;
		int h;
	} size; /* The size of the world in pixels */
	CharacterType_Or_ObjectType *typelist; /* List of characters/objects */
	int count; /* Count of how many ^ */
	Texture *background; /* Texture used for the background for the world */
} World;

/* Update the world */
void World_Update(World *w);

/* Load a world from a file */
World * NewWorld_FromFile(char *path);

/* Destroy a world */
void Destroy_World(World *w);

/* Update all of the facets in a world */
void World_Update(World *w, int frame);

/* Render all of the facets of the world */
void World_Render(World *w, SDL_Renderer, *r SDL_Rect *Camera);
