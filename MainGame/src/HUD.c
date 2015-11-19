//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../include/HUD.h"

HUD * Create_HUD(void) {
	//Load PNG textures
	swordHUDTexture = loadTexture(".png");
	staffHUDTexture = loadTexture(".png");
	bowHUDTexture = loadTexture(".png");
	heartHUDTexture = loadTexture(".png");
	
}

void renderHUD(void) {
	//Will render a number of hearts 0-5
	renderHeartsHUD();

	//Will render the weapon in bottom left
	renderWeaponHUD();
}

void renderHeartsHUD (void) {
	SDL_Rect heartDest;//Location for 1st heart
	heartDest.x = 26;
	heartDest.y = 35;
	heartDest.w = 29;
	heartDest.h = 29;

	int i;
	for(i = 0; i < (game->player->health); i++){
		SDL_RenderCopy(gRenderer, heartHUDTexture, NULL, heartDest);
		
		heartDest.x += 33;//So that next heart is moved over
	}//end for	
}

void renderWeaponHUD(void) {
	//Bottom left HUD (weapon)
	SDL_Rect weaponHUDDest;//Location for bottom HUD
	weaponHUDDest.x = 0;
	weaponHUDDest.y = 521;
	weaponHUDDest.w = 199;
	weaponHUDDest.h = 199;

	switch(game->player->weapon){
		case SWORD:
			//Render texture to screen
			SDL_RenderCopy(gRenderer, swordHUDTexture, NULL, weaponHUDDest);
		break;

		case STAFF:
			//Render texture to screen
			SDL_RenderCopy(gRenderer, staffHUDTexture, NULL, weaponHUDDest);
		break;

		case BOW:
			//Render texture to screen
			SDL_RenderCopy(gRenderer, bowHUDTexture, NULL, weaponHUDDest);
		break;
	}
}

