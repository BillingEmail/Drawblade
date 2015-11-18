/* world.c
 *
 * see world.h ok
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"
#include "../../shared/include/level.h"

World * World_LoadWorldFromLevel (Level * level) {
	


}




void World_Update(World *w) {
	
	testObjectCollision(w->Playertype, w->Objecttypes);
	
}

void World_Render(World *w, int frame, SDL_Renderer *r, SDL_Rect *Camera) {
	for (int i = 0; i < w->count; i++) {
		if (w->typelist->type == CHARACTER) {
			for (int c = 0; c < w->typelist->ct->object_type->instance_cout) {
				CharacterType_RenderCharacter(w->typelist[i].ct, renderer, c, Camera);
			}
		} else {
			for (int o = 0; o < w->typelist->ot->instance_count) {
				ObjectType_RenderObject(w->typelist[i].ot, renderer, o, Camera);
			}
		}
	}
}
