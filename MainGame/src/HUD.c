//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../include/HUD.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

HUD * Create_HUD(Container *container) {
	HUD *ret = malloc(sizeof(HUD));

	ret->textures.sword = New_Texture(container->renderer, "../../assets/img/swordHUD.png");
	ret->textures.staff = New_Texture(container->renderer, "../../assets/img/staffHUD.png");
	ret->textures.bow = New_Texture(container->renderer, "../../assets/img/bowHUD.png");
	ret->textures.heart = New_Texture(container->renderer, "../../assets/img/heartHUD.png");

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
	//Based on player health, will render hearts
	for (int i = 0; i < (game->player->health); i++){		
		Texture_Render(h->textures.heart, r, h->heartdst.x + (i * 33), 35, NULL);
	}
}

<<<<<<< HEAD
void HUD_RenderWeapon(HUD *h, SDL_Renderer *r) {
	Texture *weapon;
	switch (game->player->weapon){
=======
<<<<<<< HEAD
void renderWeaponHUD() {
=======
void renderWeaponHUD(void) {
>>>>>>> b6a124f4ac98a3401aa05e7526753bfd743b872a
	//Bottom left HUD (weapon)
	SDL_Rect weaponHUDDest;//Location for bottom HUD
	weaponHUDDest.x = 0;
	weaponHUDDest.y = 521;
	weaponHUDDest.w = 199;
	weaponHUDDest.h = 199;

	switch(game->player->weapon){
>>>>>>> e421613e16c110de941849ad51eee9e731c0bda2
		case SWORD:
			weapon = h->textures.sword;
		break;
		case STAFF:
			weapon = h->textures.staff;
		break;
		case BOW:
			weapon = h->textures.bow;
		break;
	}

	Texture_Render(r, weapon, NULL, &h->weapondst, NULL);
}

