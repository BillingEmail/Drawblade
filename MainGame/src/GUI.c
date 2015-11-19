#include "GUI.h"
#include "../../shared/include/texture.h"
//Would it be better for this to return something or have the action take place in here?
void buttonAction(int action){
switch (action){
	case 1:
	{
	//Start game stage 1
	//Main menu play button
	break;
	}

	case 2:
	{
	//Start game stage 2
	//Continue button at end of stage 1
	break;
	}

	case 3:
	{
	//Start game stage 3
	//Continue button at end of stage 2
	break;
	}

	case 4:
	{
	//Load button, will call a search function to find correct progress then load stage here
	break;
	}

	case 5:
	{
	//Return to main menu button, can be called on most screens
	break;
	}

	case 6:
	{
	//Quit game button, only available on main menu
	break;
	}
}//end switch

void addMenu(Menu thisMenu){
	addButton(thisMenu.button1);
	addButton(thisMenu.button2);
	addButton(thisMenu.button3);
}

void addButton(Button thisButton){
	//Stuff to display a button to screen
}

void checkMenu(Menu currentMenu){
	//basically go thru each button and check if clicked == true
}

}

