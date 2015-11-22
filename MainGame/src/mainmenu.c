#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "../include/mainmenu.h"
#include "../../shared/include/texture.h"
#include "../../shared/include/container.h"

bool Container_MouseClickedButton(Container *container, Button button) {
    /* Test if mouse's coords are within the texture's coords, split up x and y for readability */
    return (container->mouse.leftClick &&
	        container->mouse.x >= button.renderRect.x &&
		    container->mouse.x <= (button.renderRect.x + button.renderRect.w) &&
	        container->mouse.y >= button.renderRect.y &&
		    container->mouse.y <= (button.renderRect.y + button.renderRect.h));
}

MainMenu * New_MainMenu(Container *container) {
	MainMenu *ret = malloc(sizeof(MainMenu));
    ret->background = New_Texture(container->renderer, "../../assets/img/mainMenuBG.png");
    ret->buttons.start.texture = New_Texture(container->renderer, "../../assets/img/mainMenuStart.png");
    ret->buttons.start.texture = New_Texture(container->renderer, "../../assets/img/mainMenuQuit.png");
	ret->buttons.start.action = START;

    /* The where and size of the textures */ 
    ret->buttons.start.renderRect.x = 435;
    ret->buttons.start.renderRect.y = 200;
    ret->buttons.start.renderRect.w = 357;
    ret->buttons.start.renderRect.h = 132;

    ret->buttons.quit.renderRect.x = 435;
    ret->buttons.quit.renderRect.y = 400;
    ret->buttons.quit.renderRect.w = 357;
    ret->buttons.quit.renderRect.h = 132;

	return ret;
}

Action MainMenu_Show(MainMenu *m, Container *container) {
	Action ret;
    while (1) {
        Container_Refresh(container);
		/* Check if mouse clicked and if over a menu texture */
        if (Container_MouseClickedButton(container, m->buttons.start)) {
        	/* Mouse clicked start button */
		    ret = START;
			break;
        }
		if (Container_MouseClickedButton(container, m->buttons.quit)) {
        	/* Mouse clicked quit button */
		    ret = QUIT;
			break;
        }
        Texture_Render(m->background, container->renderer, 0, 0, NULL);
		Texture_Render(m->buttons.start.texture, container->renderer,
	               m->buttons.start.renderRect.x, m->buttons.start.renderRect.y, NULL);
		Texture_Render(m->buttons.quit.texture, container->renderer,
	               m->buttons.quit.renderRect.x, m->buttons.quit.renderRect.y, NULL);
    }

	return ret;
}

/* Destroy the main menu */
void MainMenu_Destroy(MainMenu *m) {
	Destroy_Texture(m->buttons.start.texture);
	Destroy_Texture(m->buttons.quit.texture);
	Destroy_Texture(m->background);
	free(m);
}

