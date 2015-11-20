/* world.c
 *
 * see world.h ok
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"
#include "../../shared/include/level.h"
#include "../include/player.h"
#include "../../shared/include/container.h"

World * World_LoadWorldFromLevel(Level * level) {
	World *ret = malloc(sizeof(World));
	
	ret->size.h = level->height;
	ret->size.w = level->width;
	
	ret->EnemyTypeCount = 0;
	// ret->EnemyTypes = malloc(ret->EnemyTypeCount * sizeof(CharacterType *));	
	
	ret->ObjectTypeCount = 1;
	ret->ObjectTypes = malloc(ret->ObjectTypeCount * sizeof(ObjectType *));
	
	/*
	for (int i = 0; i < EnemyTypeCount; i++) {
		switch (i) {
			case 	
	*/

	/* load all of the character types, textures and stuff */

}




void World_Update(World *w, Player *p, int frame) {	
	/* Update enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i].object_type->instance_count; i++) {
			CharacterType_UpdateCharacter(w->EnemyTypes[i], e, frame);
		}
	}

	World_RunCollisions(w, p);
	
}

void World_Render(World *w, int frame, Container *c) {
	/* Render the background first */
	Texture_Render(w->background);

	/* Render all of the objects */
	for (int i = 0; i < w->ObjectTypeCount; i++) {
		for (int o = 0; o < w->ObjectTypes[i].instance_count; o++) {
			/* TODO Check if the object is within view, only render it if so */
			/* Render the object */
			ObjectType_RenderObject(w->ObjectTypes[i], o, c);
		}
	}
	/* Render all of the characters/enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i].object_type->instance_count; e++) {
			/* TODO Check if the enemy is within view, only render it if so */
			/* Render the enemy */
			CharacterType_RenderCharacter(w->EnemyTypes[i], e, c);
		}
	}
}
