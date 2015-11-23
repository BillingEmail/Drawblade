//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../include/HUD.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"
#include "../include/player.h"

HUD * Create_HUD(Container *container) {
	HUD *ret = malloc(sizeof(HUD));
	ret->weaponTextures[SWORD] = New_Texture(container->renderer, "../../assets/img/swordHUD.png");
	ret->weaponTextures[STAFF] = New_Texture(container->renderer, "../../assets/img/staffHUD.png");
	ret->weaponTextures[BOW]   = New_Texture(container->renderer, "../../assets/img/bowHUD.png");

	ret->heartTexture = New_Texture(container->renderer, "../../assets/img/heartHUD.png");

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

void HUD_Render(HUD *h, Player *p, LevelType theme, SDL_Renderer *r) {
	//Will render a number of hearts 0-5
	HUD_RenderHearts(h, r, p);

	//Will render the weapon in bottom left
	HUD_RenderWeapon(h, r, theme);
}

void HUD_RenderHearts(HUD *h, Player *player, SDL_Renderer *r) {
	//Based on player health, will render hearts
	for (int i = 0; i < (player->health); i++){		
		Texture_Render(h->heart, r, h->heartdst.x + (i * 33), 35, NULL);
	}
}

void HUD_RenderWeapon(HUD *h, SDL_Renderer *r) {
	Texture_Render(h->weaponTextures[theme], r, h->weapondst.x, h->weapondst.y, NULL);
}

/* Destroy the HUD and it's textures */
void HUD_Destroy(HUD *h) {
	/* Destroy each HUD weapon icon texture */
	for (int i = 0; i < 3; i++) {
		Destroy_Texture(h->weaponTextures[i]);
	}
	Destroy_Texture(h->heartTexture);
	free(h);
}
