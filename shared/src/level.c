#include "../include/level.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
returns true or false depending on whether you are creating a 
new file or opening an old one respectively.
*/
Mode getMode(void) {
	char mode[5];

	//prompt the user
	printf("Do you want to create a new level or open an old level?\n" 
			"Enter New or Load: ");
	scanf("%s", mode);

	//check if they want "New" or "Load"
	if(strcmp("New", mode) == 0 || strcmp("new", mode) == 0) {
		return NEW;
	}
	if(strcmp("Load", mode) == 0 || strcmp("load", mode) == 0) {
		return LOAD;
	}
	//if not "New" or "Load"
	return FAIL;
}


/* 
This collects a string input from the user
It does this by using fgets, and then removing 
*/
char * GetFileName(void) {
	//the name of the file
	char *FileName = malloc(sizeof(char) * 64);	
	//buffer for the name
	char Buffer[16];

	//prompt the user for the name
	printf("\nEnter the name of the level: ");
	scanf("%s", Buffer);

	//concatenates the path to the name the user inputs
	strcpy(FileName, "../assets/levels/");
	strcat(FileName, Buffer);
	strcat(FileName, ".lvl");
	
	return FileName;
}

/*
This opens the file with the FileName provided from GetFileName
It runs GetFileName until the user inputs a correct input
It then returns the file pointer when it is done
*/
FILE * GetFile(void) {
	FILE *fp;
	char *FileName;
	
	//this just checks if the pointer returned by trying to use GetFileName is null
	while ((fp = fopen((FileName = GetFileName()), "rb")) == NULL) {
		printf("Could not find file %s\n", FileName);
		free(FileName);
	}
   free(FileName);
   return fp;	
}

/*
This is the main function for loading a level
this gets if you want a new level or an old level
this also opens the file using getMode() to either open an old level or create a new one

when it is done, it will return the level it has creaeted
*/
Level * New_Level(void) {
	//malloc's a single level
	Level *level = malloc(sizeof(Level));
	
	//saves the mode and checks if it failed or not
	Mode mode = getMode();
	while (mode == FAIL) {
		printf("Invalid input\n");
		mode = getMode();	
	}
	FILE *fp;

	//For opening a new level
	if (mode == NEW) {
		//prompts the user for a width and a height
		printf("\nEnter the height of the level: ");
		scanf("%d", &level->height);
		printf("Enter the width of the level: ");
		scanf("%d", &level->width);
		//sets default theme
		level->theme = MEDIEVAL;
		//callocs all of the tiles so they can be used later
		Level_CreateTiles(level);
	}
	//For opening an old level
	else {
		//gets the file name
		fp = GetFile();
		Level_LoadFromFile(level, fp);
		fclose(fp);
	}

	return level;
}

/*
This reads in the binary file that was previously written
It stores it too into a level
fread is for reading binary files basically
*/
void Level_LoadFromFile(Level *level, FILE *fp) {
	//each line reads in the number of bits in an int and stores it to each value
	fread(&level->width, sizeof(int), 1, fp);
	fread(&level->height, sizeof(int), 1, fp);
	fread(&level->theme, sizeof(int), 1, fp);	
	//callocs the tiles
	Level_CreateTiles(level);
	//reads a line of tiles of size width into tileArray per iteration 
	for (int i = 0; i < level->height; i++) {
		fread((level->tileArray[i]), sizeof(Tile), level->width, fp);
	}

}

/* The most sane way to load from a file into a structure */
Level * New_LevelFromFile(const char *path) {
	Level *ret = malloc(sizeof(Level));

	FILE *fp = fopen(path, "rb");
	if (!fp) {
		puts("Too bad");
	}

	Level_LoadFromFile(ret, fp);

	return ret;
}

/* Load a level by it's name, for convienience purposes */
Level * New_LevelByName(const char *name) {
	char path[64];

	sprintf(path, "../assets/levels/%s.lvl", name);
	return New_LevelFromFile(path);
}

/*
This saves the level to a binary file
it first opens the file with the desired file name of the user
it then fwrites it to the file with that file name
it also frees the level and tilearray in the level
*/
void Level_Save(Level *level) {
	char *FileName;
	FILE *fp;
	//opens the file
	fp = fopen((FileName = GetFileName()), "wb");
	free(FileName);
	//writes to a file just as it was read to a file
	fwrite(&level->width, sizeof(int), 1, fp);
	fwrite(&level->height, sizeof(int), 1, fp);
	fwrite(&level->theme, sizeof(int), 1, fp);
	for (int i = 0; i < level->height; i++) {
		fwrite((level->tileArray[i]), sizeof(Tile), level->width, fp);
	}
	//destroys the level
	Level_Destroy(level);

	fclose(fp);
}

/*
Goes through the array and frees everything
It then frees the actual level
*/
void Level_Destroy(Level *level) {
	for (int i = 0; i < level->height; i++) {
		free(level->tileArray[i]);
	}
	free(level->tileArray);
	free(level);
}
/*
Mallocs the giant tile array you have
It then callocs it so that every value in the array is 0
*/
void Level_CreateTiles(Level *level) {
	level->tileArray = malloc(level->height * sizeof(Tile *));
	for (int i = 0; i < level->height; i++) {
		level->tileArray[i] = calloc(level->width, sizeof(Tile));
	}
}

BrickChoice Level_GetBrickChoice(Level *level, int x, int y) {
	bool top = true;
	if (y > 0) top = !(level->tileArray[y - 1][x] == BRICK);
	bool bottom = true;
	if (y < level->height - 1) bottom =	!(level->tileArray[y + 1][x] == BRICK);
	bool left = true;
	if (x > 0) left = !(level->tileArray[y][x - 1] == BRICK);
	bool right = true;
	if (x < level->width - 1) right = !(level->tileArray[y][x + 1] == BRICK);	

	/* ayy thats my choice too */	
	int renderChoice = NUDE;

	if (top && !bottom && !left && !right) renderChoice = TOP;
	if (!top && bottom && !left && !right) renderChoice = BOTTOM;
	if (!top && !bottom && left && !right) renderChoice = LEFT;
	if (!top && !bottom && !left && right) renderChoice = RIGHT;
	if (top && !bottom && !left && right) renderChoice = TOPRIGHT;
	if (!top && bottom && left && !right) renderChoice = BOTTOMLEFT;
	if (!top && bottom && !left && right) renderChoice = RIGHTBOTTOM;
	if (top && !bottom && left && !right) renderChoice = TOPLEFT;
	if (top && !bottom && left && right) renderChoice = TOPRIGHTLEFT;
	if (top && bottom && !left && right) renderChoice = TOPRIGHTBOTTOM;
	if (!top && right && bottom && left) renderChoice = RIGHTBOTTOMLEFT;
	if (top && bottom && left && !right) renderChoice = TOPBOTTOMLEFT;
	if (top && bottom && !left && !right) renderChoice = TOPBOTTOM;
	if (!top && !bottom && left && right) renderChoice = RIGHTLEFT;
	if (top && bottom && left && right) renderChoice = ALL;

	return renderChoice;
}
