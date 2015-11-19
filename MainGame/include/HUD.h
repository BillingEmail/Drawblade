#ifndef HUD_H
#define HUD_H

typedef struct _hud {
	struct {
		Texture *sword;
		Texture *staff;
		Texture *bow;
		Texture *heart;
	} textures;

} HUD;

/* Load the media for the HUD */
HUD * Create_HUD(void);

//Calls the individual render functions
void HUD_Render(HUD *h, SDL_Renderer *r);

//Renders the hearts based on player health
void HUD_RenderHearts(HUD *h, SDL_Renderer *r);

//Renders the weapon box based on player weapon
void HUD_RenderWeapon(HUD *h, SDL_Renderer *r);

#endif
