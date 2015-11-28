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

World * NewWorld_FromFile(const char *path, Container *container) {
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
	char *brick_texture;
	char *melee_enemy_texture;
	char *ranged_enemy_texture;
	char *flying_enemy_texture;

	ret->size.h = level->height * TILE_SCALE;
	ret->size.w = level->width * TILE_SCALE;

	ret->theme = level->theme;
	ret->is_complete = false;	
	switch (level->theme) {
		case LAVA:
			ret->background.still = New_Texture(container->renderer, "../assets/img/Lava/background_still.png");
			player_texture = "../assets/img/Lava/player.png";
			brick_texture = "../assets/img/Lava/brick.png";
			melee_enemy_texture = "../assets/img/Lava/melee_enemy.png";
			ranged_enemy_texture = "../assets/img/Lava/melee_enemy.png";
			flying_enemy_texture = "../assets/img/Lava/flying_enemy.png";			
		break;
		case MEDIEVAL:
			ret->background.still = New_Texture(container->renderer, "../assets/img/Medieval/background_still.png");
			player_texture = "../assets/img/Medieval/player.png";
			brick_texture = "../assets/img/Medieval/brick.png";
			melee_enemy_texture = "../assets/img/Medieval/melee_enemy.png";
			ranged_enemy_texture = "../assets/img/Medieval/melee_enemy.png";
			flying_enemy_texture = "../assets/img/Medieval/flying_enemy.png";
		break;
		case ICE:
			ret->background.still = New_Texture(container->renderer, "../assets/img/Ice/background_still.png");
			player_texture = "../assets/img/Ice/player.png";
			brick_texture = "../assets/img/Ice/brick.png";
			melee_enemy_texture = "../assets/img/Ice/melee_enemy.png";
			ranged_enemy_texture = "../assets/img/Ice/melee_enemy.png";
			flying_enemy_texture = "../assets/img/Ice/flying_enemy.png";
		break;
		case SPOOKY:
			ret->background.still = New_Texture(container->renderer, "../assets/img/Medieval/background_still.png");
			player_texture = "../assets/img/Spooky/player.png";
			brick_texture = "../assets/img/Spooky/brick.png";
			melee_enemy_texture = "../assets/img/Spooky/melee_enemy.png";
			ranged_enemy_texture = "../assets/img/Spooky/melee_enemy.png";
			flying_enemy_texture = "../assets/img/Spook/flying_enemy.png";					
		break;
	}

	ret->player = New_Player(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(
					container->renderer, player_texture
				),
				10,
				8, 8, 4, 4, 3, 3, 2, 2, 1, 1
			),
			26, 36
		),
		0, 0
	);
	ret->player->traits->hitpoints = 5;

	ret->EnemyTypeCount = 3;
	ret->EnemyTypes = malloc(ret->EnemyTypeCount * sizeof(CharacterType *));	
	
	ret->EnemyTypes[0] = New_CharacterType(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(container->renderer, melee_enemy_texture),
				10,
				8, 8, 4, 4, 3, 3, 2, 2, 1, 1
			),
			31, 33
		),
		0, 0
	);

	ret->EnemyTypes[1] = New_CharacterType(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(container->renderer, ranged_enemy_texture),
				10,
				8, 8, 4, 4, 3, 3, 2, 2, 1, 1
			),
			31, 33
		),
		0, 0
	);

	ret->EnemyTypes[2] = New_CharacterType(
		New_ObjectType(
			New_Spritesheet(
				New_Texture(container->renderer, flying_enemy_texture),
				6,
				4, 4, 3, 3, 2, 2
			),
			34, 33
		),
		0, 0
	);

	ret->ObjectTypeCount = 1;
	ret->ObjectTypes = malloc(ret->ObjectTypeCount * sizeof(ObjectType *));

	ret->ObjectTypes[OBJECT_BRICK] = New_ObjectType(
		New_Spritesheet(
			New_Texture(container->renderer, brick_texture),
			1, 16
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
					ret->ObjectTypes[OBJECT_BRICK]->instances[ret->ObjectTypes[OBJECT_BRICK]->instance_count - 1].sprite_index[0] = Level_GetBrickChoice(level, x, y);
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
/* Behold satya's great work
void World_SetBrickSprites(World *w, int instance) {
	bool top = false;
	bool bottom = false;
	bool left = false;
	bool right = false;
	int renderChoice = NUDE;
		for (int i = 0; i < w->ObjectTypes[OBJECT_BRICK]->instance_count; i++) {
			if (i != instance) {
				if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.x == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.x - 32) {
					if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.y == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.y) {
						left = true;
					}
				}
				if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.x == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.x + 32) {
					if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.y == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.y) {
						right = true;
					}
				}
				if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.x == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.x) {
					if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.y == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.y + 32) {
						top = true;
					}
				}
				if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.x == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.x - 32) {
					if (w->ObjectTypes[OBJECT_BRICK]->instances[i].dstrect.y == w->ObjectTypes[OBJECT_BRICK]->instances[instance].dstrect.y) {
						bottom = true;
					}
				}
			}
		}
	
	/ * 
	TODO  set the sprites now that you have found out which is true 
	I want to move the bool checking into a function, and then the last thing should be seting the spritesheet position
	I also need to move the enum from leveleditor.h to somewhere else (brick.h?)
	maybe we can move the checks into that
	* /

}
*/

void World_Update(World *w, unsigned int dt, Container *container) {	
	/* Update enemies */
	for (int i = 0; i < w->EnemyTypeCount; i++) {
		for (int e = 0; e < w->EnemyTypes[i]->object_type->instance_count; i++) {
			CharacterType_UpdateCharacter(w->EnemyTypes[i], dt, e);
		}
	}
	Player_Update(w->player, dt, container);
	World_RunCollisions(w);	
}

void World_Render(World *w, unsigned int dt, Container *container) {
	/* Render the background first */
	Texture_Render(w->background.still, container->renderer, 0, 0, NULL);


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
	Destroy_Texture(w->background.still);
	free(w);
}
