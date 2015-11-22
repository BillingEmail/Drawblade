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
	printf("Do you want to create a new file or open an old file?\n" 
			"Type New or Load:\n");
	scanf("%s", mode);

	//check if they want "New" or "Load"
	if(strcmp("New", mode) || strcmp("new", mode)) {
		return NEW;
	}
	if(strcmp("Load", mode) || strcmp("load", mode)) {
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
	char *FileName = malloc(sizeof(char) * 64);	
	char Buffer[16];
	printf("\nEnter the name of the File: ");
	strcpy(FileName, "../assets/levels/");
	scanf("%s", Buffer);
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
	Mode mode = getMode();
	while (mode == FAIL) {
		printf("Invalid input\n");
		mode = getMode();	
	}
	FILE *fp;

	//For opening a new level
	if (mode == NEW) {
		//defaults
		printf("\nWhat is the height you want for your level?\n");
		scanf("%d", &level->height);
		printf("What is the width you want for your level?\n");
		scanf("%d", &level->width);
		level->theme = LAVA;
		CreateTiles(level);
	}
	//For opening an old level
	else {
		fp = GetFile();
		LoadLevelFromFile(level, fp);
		fclose(fp);
	}

	return level;
}

/*
This reads in the binary file that was previously written
It stores it too into a level
fread is for reading binary files basically
*/
void LoadLevelFromFile(Level *level, FILE *fp) {
	fread(&level->width, sizeof(int), 1, fp);
	fread(&level->height, sizeof(int), 1, fp);
	fread(&level->theme, sizeof(int), 1, fp);	
	CreateTiles(level);
	
	for (int i = 0; i < level->height; i++) {
		fread((level->tileArray[i]), sizeof(Tile), level->width, fp);
	}

	
}

/*
This saves the level to a binary file
it first opens the file with the desired file name of the user
it then fwrites it to the file with that file name
it also frees the level and tilearray in the level
*/
void SaveLevel(Level *level) {
	char *FileName;
	FILE *fp;

	fp = fopen((FileName = GetFileName()), "wb");
	free(FileName);

	fwrite(&level->width, sizeof(int), 1, fp);
	fwrite(&level->height, sizeof(int), 1, fp);
	fwrite(&level->theme, sizeof(int), 1, fp);
	for (int i = 0; i < level->height; i++) {
		fwrite((level->tileArray[i]), sizeof(Tile), level->width, fp);
	}
	DestroyLevel(level);

	fclose(fp);
}

/*
Goes through the array and frees everything
It then frees the actual level
*/
void DestroyLevel(Level *level) {
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
void CreateTiles(Level *level) {
	level->tileArray = malloc(level->height * sizeof(Tile *));
	for (int i = 0; i < level->height; i++) {
		level->tileArray[i] = calloc(level->width, sizeof(Tile));
	}
}
