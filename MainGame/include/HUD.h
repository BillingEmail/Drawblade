#ifndef HUD_H
#define HUD_H
#include "../../shared/include/container.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/level.h"
#include "../include/player.h"
typedef struct _hud {
	Texture **weaponTextures;
	Texture *heartFullTexture;
	Texture *heartEmptyTexture;

	SDL_Rect heartdst;
	SDL_Rect weapondst;

} HUD;

/* Load the media for the HUD */
HUD * Create_HUD(Container *c);

//Calls the individual render functions
void HUD_Render(HUD *h, Player *player, LevelType theme, Container *container);

//Renders the hearts based on player health
void HUD_RenderHearts(HUD *h, Player *player, Container *container);

//Renders the weapon box based on player weapon
void HUD_RenderWeapon(HUD *h, LevelType theme, Container *container);

/* Destroy the HUD and it's textures */
void HUD_Destroy(HUD *h);

#endif
