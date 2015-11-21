#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../include/mainmenu.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

int Show_Main_Menu(Container *container) {
    Texture *MainMenuBG = New_Texture(container->renderer, "../../assets/img/mainMenuBG.png");
    Texture *MainMenuStart = New_Texture(container->renderer, "../../assets/img/mainMenuStart.png");
    Texture *MainMenuQuit = New_Texture(container->renderer, "../../assets/img/mainMenuQuit.png");

    /* The where and size of the textures */
    SDL_Rect MainMenuStartDest;
    MainMenuStartDest.x = 435;
    MainMenuStartDest.y = 200;
    MainMenuStartDest.w = 357;
    MainMenuStartDest.h = 132;

    SDL_Rect MainMenuQuitDest;
    MainMenuQuitDest.x = 435;
    MainMenuQuitDest.y = 400;
    MainMenuQuitDest.w = 357;
    MainMenuQuitDest.h = 132;


    while (1) {
        Container_Refresh(container);
	/* Check if mouse clicked and if over a menu texture */
        if(container->mouse.leftClick && Check_Mouse_Over_Button(container, MainMenuStartDest)) {
            return PLAY;
        }
	if(container->mouse.leftClick && Check_Mouse_Over_Button(container, MainMenuQuitDest)) {
            return QUIT;
        }
        Texture_Render(MainMenuBG, container->renderer, 0, 0);
	Texture_Render(MainMenuStart, container->renderer, MainMenuStartDest.x, MainMenuStartDest.y);
	Texture_Render(MainMenuQuit, container->renderer, MainMenuQuitDest.x, MainMenuQuitDest.y);
    }
	Destroy_Texture(MainMenuBG);
	Destroy_Texture(MainMenuStart);
	Destroy_Texture(MainMenuQuit);
}


bool Check_Mouse_Over_Button(Container *container, SDL_Rect *testingRect){
    bool ret = false;
    /* Test if mouse's coords are within the texture's coords, split up x and y for readability */
    if(container->mouse.x >= testingRect.x && container->mouse.x <= (testingRect.x + testingRect.w)){
	if(container->mouse.y >= testingRect.y && container->mouse.y <= (testingRect.y + testingRect.h)){
	    ret = true;
	}
    }
    return ret;
}
