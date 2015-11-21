#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../include/startScreen.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

void Show_Start_Screen(Container *container) {
    Texture *StartScreen = Load_Texture(container->renderer, "../../assets/img/startScreen.png");
    while (1) {//Loops forever
        Container_Refresh(container);//Will be used to read mouse events
        if(container->mouse.leftClick) {
            break;
        }
        Texture_Render(container->renderer, StartScreen, 0, 0);
    }
}
