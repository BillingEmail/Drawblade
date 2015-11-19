//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "../include/HUD.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//All HUD textures to be displayed
SDL_Texture* swordHUDTexture = NULL;
SDL_Texture* staffHUDTexture = NULL;
SDL_Texture* bowHUDTexture = NULL;
SDL_Texture* heartHUDTexture = NULL;


int main( int argc, char* args[] )
{
	//Start up SDL and create window
	init();
	
	//Load media
	loadHUDMedia();	
			
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while( !quit )
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		
		//Clear screen
		SDL_RenderClear( gRenderer );
		
		renderHUD();		

		//Update screen
		SDL_RenderPresent(gRenderer);
	}

	//Free resources and close SDL
	close();

	return 0;
}

void init()
{
	//Initialize SDL
	SDL_Init( SDL_INIT_VIDEO );

	//Set texture filtering to linear
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	//Create window
	gWindow = SDL_CreateWindow( "Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

	//Create renderer for window
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );

	//Initialize renderer color
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	IMG_Init( imgFlags );
}

void loadHUDMedia()
{
	//Load PNG textures
	swordHUDTexture = loadTexture(".png");
	staffHUDTexture = loadTexture(".png");
	bowHUDTexture = loadTexture(".png");
	heartHUDTexture = loadTexture(".png");
	
}

void close()
{
	//Free loaded images
	SDL_DestroyTexture(swordHUDTexture);
	swordHUDTexture = NULL;
	SDL_DestroyTexture(staffHUDTexture);
	staffHUDTexture = NULL;
	SDL_DestroyTexture(bowHUDTexture);
	bowHUDTexture = NULL;
	SDL_DestroyTexture(heartHUDTexture);
	heartHUDTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
	//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		
	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}

void renderHUD(){
	//Will render a number of hearts 0-5
	renderHeartsHUD();

	//Will render the weapon in bottom left
	renderWeaponHUD();
}

void renderHeartsHUD(){
	SDL_Rect heartDest;//Location for 1st heart
	heartDest.x = 26;
	heartDest.y = 35;
	heartDest.w = 29;
	heartDest.h = 29;

	int i;
	for(i = 0; i < (game->player->health); i++){
		SDL_RenderCopy(gRenderer, heartHUDTexture, NULL, heartDest);
		
		heartDest.x += 33;//So that next heart is moved over
	}//end for	
}

void renderWeaponHUD() {
	//Bottom left HUD (weapon)
	SDL_Rect weaponHUDDest;//Location for bottom HUD
	weaponHUDDest.x = 0;
	weaponHUDDest.y = 521;
	weaponHUDDest.w = 199;
	weaponHUDDest.h = 199;

	switch(game->player->weapon){
	case SWORD:
	{
	//Render texture to screen
	SDL_RenderCopy(gRenderer, swordHUDTexture, NULL, weaponHUDDest);
	break;
	}//end case 1

	case STAFF:
	{
	//Render texture to screen
	SDL_RenderCopy(gRenderer, staffHUDTexture, NULL, weaponHUDDest);
	break;
	}//end case 2

	case BOW:
	{
	//Render texture to screen
	SDL_RenderCopy(gRenderer, bowHUDTexture, NULL, weaponHUDDest);
	break;
	}//end case 3
	}//end switch
}

