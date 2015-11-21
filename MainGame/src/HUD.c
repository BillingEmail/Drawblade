//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../include/HUD.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

HUD * Create_HUD(Container *c) {
	HUD *ret = malloc(sizeof(HUD));

	ret->textures.sword = Load_Texture(container->renderer, "../../assets/img/swordHUD.png");
	ret->textures.staff = Load_Texture(container->renderer, "../../assets/img/staffHUD.png");
	ret->textures.bow = Load_Texture(container->renderer, "../../assets/img/bowHUD.png");
	ret->textures.heart = Load_Texture(container->renderer, "../../assets/img/heartHUD.png");

	ret->heartdst.x = 26;
	ret->heartdst.y = 35;
	ret->heartdst.w = 29;
	ret->heartdst.h = 29;

	ret->weapondst.x = 0;
	ret->weapondst.y = 521;
	ret->weapondst.w = 199;
	ret->weapondst.h = 199;

	return ret;
}

void HUD_Render(HUD *h, SDL_Renderer *r) {
	//Will render a number of hearts 0-5
	renderHeartsHUD(h, r);

	//Will render the weapon in bottom left
	renderWeaponHUD(h, r);
}

void HUD_RenderHearts(HUD *h, SDL_Renderer *r) {
	for (int i = 0; i < (game->player->health); i++){		
		Texture_Render(h->textures.heart, r, h->heartdst.x + (i * 33), 35, NULL);
	}
}


void HUD_RenderWeapon(HUD *h, SDL_Renderer *r) {
	Texture *weapon;
	//Bottom left HUD (weapon)
	SDL_Rect weaponHUDDest;//Location for bottom HUD
	weaponHUDDest.x = 0;
	weaponHUDDest.y = 521;
	weaponHUDDest.w = 199;
	weaponHUDDest.h = 199;

	switch(game->player->weapon){
		case SWORD:
			//Render texture to screen
			weapon = h->textures.sword;
		break;
		case STAFF:
			//Render texture to screen
			weapon = h->textures.staff;
		break;
		case BOW:
			weapon = h->textures.bow;
		break;
	}

	Texture_Render(r, weapon, NULL, &h->weapondst, NULL);
}

