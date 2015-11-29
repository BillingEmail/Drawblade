#ifndef HUD_H
#define HUD_H
#include "../../shared/include/container.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/level.h"
#include "../include/player.h"
typedef struct _hud {
	Texture **weaponTextures;
	Texture *actionFrameTexture;
	Texture *actionBarTexture;
	Texture *healthbarTexture;

	SDL_Rect heartdst;
	SDL_Rect weapondst;
	SDL_Rect actionframedst;
	SDL_Rect actionbardst;
	SDL_Rect actionframe2dst;
	SDL_Rect healthbardst;

} HUD;

/* Load the media for the HUD */
HUD * Create_HUD(Container *c);

//Calls the individual render functions
void HUD_Render(HUD *h, Player *player, LevelType theme, Container *container);

//Renders the hearts based on player health
void HUD_RenderHearts(HUD *h, Player *player, Container *container);

//Renders the weapon box based on player weapon
void HUD_RenderWeapon(HUD *h, LevelType theme, Container *container);

//Renders a visual representation of number of attacks player has (mana/stamina)
void HUD_RenderActionBar(HUD *h, Player *player, Container *container);

/* Destroy the HUD and it's textures */
void HUD_Destroy(HUD *h);

#endif
