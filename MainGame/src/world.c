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

World * NewWorld_FromFile(char *path, Container *container) {
	World *ret;
	Level *level = malloc(sizeof(Level));
	FILE *why_satya = fopen(path, "rb");
	Level_LoadFromFile(level, why_satya);
	fclose(why_satya);

	ret = World_LoadWorldFromLevel(level, container);

	Level_Destroy(level);

	return ret;
}

World * World_LoadWorldFromLevel(Level * level, Container *container) {
	World *ret = malloc(sizeof(World));
	char *player_texture;
	ret->size.h = level->height * TILE_SCALE;
	ret->size.w = level->width * TILE_SCALE;

	ret->theme = level->theme;
	ret->is_complete = false;	
	switch (level->theme) {
		case LAVA:
			ret->background = New_Texture(container->renderer, "../assets/img/Lava/background.png");
			player_texture = "../assets/img/Lava/player.png";
		break;
		case MEDIEVAL:
			ret->background = New_Texture(container->renderer, "../assets/img/Medieval/background.png");
			player_texture = "../assets/img/Medieval/player.png";
		break;
		case ICE:
			ret->background = New_Texture(container->renderer, "../assets/img/Ice/backround.png");
			player_texture = "../assets/img/Ice/player.png";
		break;
		case SPOOKY:
			ret->background = New_Texture(container->renderer, "../assets/img/Medieval/background.png");
			player_texture = "../assets/img/Spooky/player.png";
		break;
	}

	ret->player = New_Player(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(
					container->renderer, player_texture
				),
				4,
				8, 8, 4, 4
			),
			23, 32
		),
		0, 0
	);
	ret->player->traits->hitpoints = 5;

	for (int i = 0; i < 4; i++) {
		printf("player %d\n", ret->player->object->sprite_index[i]);
	}
	ret->EnemyTypeCount = 0;
//	ret->EnemyTypes = malloc(ret->EnemyTypeCount * sizeof(CharacterType *));	
	
	ret->ObjectTypeCount = 1;
	ret->ObjectTypes = malloc(ret->ObjectTypeCount * sizeof(ObjectType *));

	ret->ObjectTypes[OBJECT_BRICK] = New_ObjectType(
		New_Spritesheet(
			New_Texture(
				container->renderer,
				"../assets/img/brick.png"
			),
			1, 1
		),
		TILE_SCALE, TILE_SCALE /* width, height */
	);

/*	TODO ret->EnemyTypes[ENEMY_1] = New_CharacterType FINISH THIS WHEN ENEMIES FINAL */

	/* Collect and load instances from level tiles */
	for (int y = 0; y < level->height; y++) {
		for (int x = 0; x < level->width; x++) {
			switch (level->tileArray[y][x]) {
				case BRICK:
					ObjectType_AddObject(ret->ObjectTypes[OBJECT_BRICK], x * TILE_SCALE, y * TILE_SCALE);
				break;
				case PLAYER:

					ret->player->object->dstrect.x = x * TILE_SCALE;
					ret->player->object->dstrect.y = y * TILE_SCALE;
				break;
				default:
				break;
			}
		}
	}

	return ret;
}

void World_Update(World *w, unsigned int dt, Container *container) {	
	/* Update enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i]->object_type->instance_count; i++) {
			CharacterType_UpdateCharacter(w->EnemyTypes[i], dt, e);
		}
	}
	World_RunCollisions(w);	
	Player_Update(w->player, dt, container);
}

void World_Render(World *w, unsigned int dt, Container *container) {
	/* Render the background first */
	Texture_Render(w->background, container->renderer, 0, 0, NULL);


	/* Render all of the objects */
	for (int i = 0; i < w->ObjectTypeCount; i++) {
		for (int o = 0; o < w->ObjectTypes[i]->instance_count; o++) {
			/* TODO Check if the object is within view, only render it if so */
			/* Render the object */
			ObjectType_RenderObject(w->ObjectTypes[i], o, dt, container);
//			SDL_SetRenderDrawColor(container->renderer, 255, 0, 0, 128);
//			SDL_RenderFillRect(container->renderer, &w->ObjectTypes[i]->instances[o].dstrect);
		}
	}
	/* Render all of the characters/enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i]->object_type->instance_count; e++) {
			/* TODO Check if the enemy is within view, only render it if so */
			/* Render the enemy */
//			CharacterType_RenderCharacter(w->EnemyTypes[i], e, container);
		}
	}
	Player_Render(w->player, dt, container);
}

void World_Destroy(World *w) {
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		Destroy_CharacterType(w->EnemyTypes[i]);
	}
	for (int i = 0; i < w->ObjectTypeCount; i++) {
		Destroy_ObjectType(w->ObjectTypes[i]);
	}
	Destroy_Player(w->player);
	Destroy_Texture(w->background);
	free(w);
}
