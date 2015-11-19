#ifndef HUD_H
#define HUD_H


//Starts up SDL and creates window
void init(void);

//Loads media
bool loadHUDMedia(void);

//Frees media and shuts down SDL
void close(void);

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//Calls the individual render functions
void renderHUD(void);

//Renders the hearts based on player health
void renderHeartsHUD(void);

//Renders the weapon box based on player weapon
void renderWeaponHUD(void);


#endif
