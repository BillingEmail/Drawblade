/* world.c
 *
 * see world.h ok
 */

#include <stdio.h>
#include <stdlib.h>
#include "../include/world.h"

World * NewWorld_FromFile(char *path) {
	World *ret;
	FILE *file;
	int **map;

	ret = malloc(sizeof(World));
	if (!ret) {
		fprintf(stderr, "Error: could not allocate memory for world\n");
		return NULL;
	}
	
	file = fopen(path, "rb");
	if (!file) {
		fprintf(stderr, "Error: could not open world file: %s\n", path);
		free(ret);
		return NULL;
	}

	fread(&ret->size.w, sizeof(int), 1, file);
	fread(&ret->size.h, sizeof(int), 1, file);
	printf("w: %d\nh: %d\n", ret->size.w, ret->size.h);

	/* Create 2d array for the map */
	map = malloc(ret->size.w * sizeof(int *));
	for (int i = 0; i < ret->size.w; i++) {
		map[i] = malloc(ret->size.h * sizeof(int));
		/* Read in that column of the map */
		fread(map[i], sizeof(int), ret->size.w, file);
	}

	for (int i = 0; i < ret->size.w; i++) {
		for (int k = 0; k < ret->size.h; k++) {
			printf("%2d ", map[i][k]);
		}
		free(map[i]);
		putchar('\n');
	}

	free(map);
	fclose(file);
	return ret;
}

/* Iterate through every object and character in the world and update,
 * not render
 */
void World_Update(World *w, int frame) {
	for (int i = 0; i < w->count; i++) {
		if (w->typelist->type == CHARACTER) {
			for (int c = 0; c < w->typelist->ct->object_type->instance_cout) {
				CharacterType_UpdateCharacter(w->typelist[i].ct, c, frame);
			}
		} else {
			for (int o = 0; o < w->typelist->ot->instance_count) {
				ObjectType_UpdateObject(w->typelist[i].ot, o, frame);
			}
		}
	}
}

void World_Render(World *w, SDL_Renderer *r, SDL_Rect *Camera) {
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
