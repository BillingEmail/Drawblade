#ifndef HUD_H
#define HUD_H
#include "../../shared/include/container.h"


typedef struct _hud {
	struct {
		Texture *sword;
		Texture *staff;
		Texture *bow;
		Texture *heart;
	} textures;
	SDL_Rect heartdst;
	SDL_Rect weapondst;

} HUD;

/* Load the media for the HUD */
HUD * Create_HUD(Container *c);

//Calls the individual render functions
void HUD_Render(HUD *h, SDL_Renderer *r);

//Renders the hearts based on player health
void HUD_RenderHearts(HUD *h, SDL_Renderer *r);

//Renders the weapon box based on player weapon
void HUD_RenderWeapon(HUD *h, SDL_Renderer *r);

#endif
