/* world.c
 *
 * see world.h ok
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"
#include "../../shared/include/level.h"
#include "../include/collisions.h"
#include "../include/player.h"
#include "../../shared/include/container.h"

World * World_LoadWorldFromLevel(Level * level, Player *p, Container *container) {
	World *ret = malloc(sizeof(World));
	
	ret->size.h = level->height * 64;
	ret->size.w = level->width * 64;
	
	ret->EnemyTypeCount = 0;
	ret->EnemyTypes = malloc(ret->EnemyTypeCount * sizeof(CharacterType *));	
	
	ret->ObjectTypeCount = 2;
	ret->ObjectTypes = malloc(ret->ObjectTypeCount * sizeof(ObjectType *));

	ret->ObjectTypes[OBJECT_BRICK] = New_ObjectType(
		New_Spritesheet(
			New_Texture(
				container->renderer,
				"../assets/img/brick.png"
			),
			1, 1
		),
		64, 64 /* width, height */
	);

/*	TODO ret->EnemyTypes[ENEMY_1] = New_CharacterType FINISH THIS WHEN ENEMIES FINAL */

	/* Collect and load instances from level tiles */
	for (int y = 0; y < level->height; y++) {
		for (int x = 0; x < level->width; x++) {
			switch (level->tileArray[y][x]) {
				case BRICK:
					ObjectType_AddObject(ret->ObjectTypes[OBJECT_BRICK], x * 64, y * 64, 0, 0);
				break;
				case PLAYER:
					p->object->dstrect.x = x * 64;
					p->object->dstrect.y = y * 64;
				break;
			}
		}
	}

	return ret;
}

void World_Update(World *w, Player *p, int frame) {	
	/* Update enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i]->object_type->instance_count; i++) {
			CharacterType_UpdateCharacter(w->EnemyTypes[i], e, frame);
		}
	}

	World_RunCollisions(w, p);	
}

void World_Render(World *w, int frame, Container *container) {
	/* Render the background first */
	Texture_Render(w->background, container->renderer, 0, 0, NULL);

	/* Render all of the objects */
	for (int i = 0; i < w->ObjectTypeCount; i++) {
		for (int o = 0; o < w->ObjectTypes[i]->instance_count; o++) {
			/* TODO Check if the object is within view, only render it if so */
			/* Render the object */
			ObjectType_RenderObject(w->ObjectTypes[i], o, container);
		}
	}
	/* Render all of the characters/enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i]->object_type->instance_count; e++) {
			/* TODO Check if the enemy is within view, only render it if so */
			/* Render the enemy */
			CharacterType_RenderCharacter(w->EnemyTypes[i], e, container);
		}
	}
}
