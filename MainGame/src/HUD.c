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

	ret->actionFrameTexture = New_Texture(container->renderer, "../assets/img/HUD/actionframe.png");
	ret->actionBarTexture = New_Texture(container->renderer, "../assets/img/HUD/actionbar.png");
	ret->healthBarTexture = New_Texture(container->renderer, "../assets/img/HUD/healthbar.png");

	ret->actionframedst.x = 1;
	ret->actionframedst.y = 48;
	ret->actionframedst.w = 204;
	ret->actionframedst.h = 14;

	ret->actionbardst.x = 3;
	ret->actionbardst.y = 50;
	ret->actionbardst.w = 1;
	ret->actionbardst.h = 10;

	ret->actionframe2dst.x = 1;
	ret->actionframe2dst.y = 35;
	ret->actionframe2dst.w = 204;
	ret->actionframe2dst.h = 14;

	ret->healthbardst.x = 3;
	ret->healthbardst.y = 37;
	ret->healthbardst.w = 1;
	ret->healthbardst.h = 10;

	return ret;
}

void HUD_Render(HUD *h, Player *p, LevelType theme, Container *container) {
	//Will render a number of hearts 0-5
	HUD_RenderHearts(h, p, container); 




	//Will render the action bar in top left
	HUD_RenderActionBar(h, p, container);
}

void HUD_RenderHearts(HUD *h, Player *player, Container *container) {
	//Renders the frame
	Texture_Render(h->actionFrameTexture, container->renderer, h->actionframe2dst.x, h->actionframe2dst.y, NULL);
	//Based on player health, will render health bar
	for (int i = 0; i < (player->traits->hitpoints)*40; i++){		
		Texture_Render(h->healthBarTexture, container->renderer, h->healthbardst.x + i, h->healthbardst.y, NULL);
	}
}

void HUD_RenderActionBar(HUD *h, Player *player, Container *container) {
	Texture_Render(h->actionFrameTexture, container->renderer, h->actionframedst.x, h->actionframedst.y, NULL);
	//For rendering the action bar with amount filled related to numactions player has
	for (int i = 0; i < (player->traits->numActions)*2; i++) {
		Texture_Render(h->actionBarTexture, container->renderer, h->actionbardst.x + i, h->actionbardst.y, NULL);
	}

}

/* Destroy the HUD and it's textures */
void HUD_Destroy(HUD *h) {
	Destroy_Texture(h->healthBarTexture);
	Destroy_Texture(h->actionBarTexture);
	Destroy_Texture(h->actionFrameTexture);
	free(h);
}
