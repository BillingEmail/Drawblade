//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../include/HUD.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"
#include "../include/player.h"
#include "../../shared/include/level.h"

HUD * Create_HUD(Container *container) {
	HUD *ret = malloc(sizeof(HUD));
	ret->weaponTextures = malloc(4 * sizeof(Texture));
	ret->weaponTextures[LAVA]     = New_Texture(container->renderer, "../assets/img/HUD/sword.png");
	ret->weaponTextures[MEDIEVAL] = New_Texture(container->renderer, "../assets/img/HUD/staff.png");
	ret->weaponTextures[SPOOKY]   = New_Texture(container->renderer, "../assets/img/HUD/bow.png");
	ret->weaponTextures[ICE]      = New_Texture(container->renderer, "../assets/img/HUD/bow.png");

	ret->heartFullTexture = New_Texture(container->renderer, "../assets/img/HUD/heartfull.png");
	ret->heartEmptyTexture = New_Texture(container->renderer, "../assets/img/HUD/heartempty.png");

	ret->heartdst.x = 1;
	ret->heartdst.y = 35;
	ret->heartdst.w = 21;
	ret->heartdst.h = 19;

	ret->weapondst.x = 0;
	ret->weapondst.y = 521;
	ret->weapondst.w = 199;
	ret->weapondst.h = 199;

	ret->actionFrameTexture = New_Texture(container->renderer, "../assets/img/HUD/actionframe.png");
	ret->actionBarTexture = New_Texture(container->renderer, "../assets/img/HUD/actionbar.png");

	ret->actionframedst.x = 1;
	ret->actionframedst.y = 64;
	ret->actionframedst.w = 204;
	ret->actionframedst.h = 24;

	ret->actionbardst.x = 3;
	ret->actionbardst.y = 66;
	ret->actionbardst.w = 20;
	ret->actionbardst.h = 20;

	return ret;
}

void HUD_Render(HUD *h, Player *p, LevelType theme, Container *container) {
	//Will render a number of hearts 0-5
	HUD_RenderHearts(h, p, container); 

	//Will render the weapon in bottom left
	HUD_RenderWeapon(h, theme, container);

	//Will render the action bar in top left
	HUD_RenderActionBar(h, p, container);
}

void HUD_RenderHearts(HUD *h, Player *player, Container *container) {
	//Based on player health, will render hearts
	for (int i = 0; i < player->traits->hitpoints; i++){		
		Texture_Render(h->heartFullTexture, container->renderer, h->heartdst.x + (i * 21) + 5, 5, NULL);
	}
	for (int i = player->traits->hitpoints; i < 5; i++) {
		Texture_Render(h->heartEmptyTexture, container->renderer, h->heartdst.x + (i * 21) + 5, 5, NULL);
	}
}

void HUD_RenderWeapon(HUD *h, LevelType theme, Container *container) {
	Texture_Render(h->weaponTextures[theme], container->renderer, h->weapondst.x, h->weapondst.y, NULL);
}

void HUD_RenderActionBar(HUD *h, Player *player, Container *container) {
	Texture_Render(h->actionFrameTexture, container->renderer, h->actionframedst.x, h->actionframedst.y, NULL);
	//For rendering the action bar with amount filled related to numactions player has
	for (int i = 0; i < player->numActions; i++) {
		Texture_Render(h->actionBarTexture, container->renderer, h->actionbardst.x + i * 20, h->actionbardst.y, NULL);
	}
}

/* Destroy the HUD and it's textures */
void HUD_Destroy(HUD *h) {
	/* Destroy each HUD weapon icon texture */
	for (int i = 0; i < 3; i++) {
		Destroy_Texture(h->weaponTextures[i]);
	}
	free(h->weaponTextures);

	Destroy_Texture(h->heartFullTexture);
	Destroy_Texture(h->heartEmptyTexture);
	Destroy_Texture(h->actionBarTexture);
	Destroy_Texture(h->actionFrameTexture);
	free(h);
}
