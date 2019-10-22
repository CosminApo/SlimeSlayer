#include <iostream>
#include <SDL.h>
#include "GameManager.h"

const int xResolution = 1280;
const int yResolution = 720;

int main(int argc, char *argv[])
{
	GameManager manager;
	manager.init(xResolution, yResolution); //initialise the game
	while (manager.getisRunning())
	{
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), manager.getTick() + 16)); //locks FPS to 60
		manager.HandleEvents(); //handle any inputs 
		if (manager.getIsMenuOpen()) //if the menu is open
		{
			manager.handleMenu();
		}
		else //if the menu isn't open it means the game is running
		{
			manager.update(); //call update functions for all objects
		}
		
		manager.render(); //display output
	}
	manager.clean();
	return 0;
}