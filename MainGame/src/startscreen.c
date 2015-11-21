#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "../include/startscreen.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

void Show_Start_Screen(Container *container) {
    Texture *StartScreen = New_Texture(container->renderer, "../../assets/img/startScreen.png");
	/* Until the user clicks */
    while (1) {
        Container_Refresh(container);
		/* Break on click */
        if(container->mouse.leftClick) {
            break;
        }
        Texture_Render(StartScreen, container->renderer, 0, 0);
    }
	Destroy_Texture(StartScreen);
}
