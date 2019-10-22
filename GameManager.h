#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "SDL.h"
#include <iostream> /* std::cout */
#include <list> /* std::list<Type> */
#include "GameObject.h"
#include "slime.h"
#include "Player.h"
#include "backgroundManager.h"
#include "uiManager.h"
#include "Platform.h" 
#include "SDL_mixer.h" /*audio*/
#include <time.h> /*time*/
#include <stdlib.h>  /*rand, srand*/
#include "audioManager.h"
#include "Explosion.h"
#include "SDL_ttf.h"
#include "uiManager.h"
#include "Button.h"

class GameManager
{
private:
	
	SDL_Window* myWindow;
	SDL_Renderer* myRenderer;
	int level;
	bool isRunning;
	long tick;
	SDL_Event Event;
	audioManager myAudioManager;
	int monsterCount;
	bool isPlayerAlive;
	bool menuIsOpen;

public:
	static bool Keys[322]; //number of SDL_KeyDown events
	static std::list<GameObject*> entities;

	void handleMenu();
	bool getIsMenuOpen() { return menuIsOpen; }
	void loadEndGameScreen();
	void loadMenu();
	void HandleEvents();
	void init(int xResolution, int yResolution);
	int update();
	void render();
	void clean();
	long getTick() { return tick; }
	void loadLevel(bool _isFirst);
	int countEntitiesWithTag(std::string _tag);
	void nextLevel();
	bool getisRunning() { return isRunning; }
	GameManager();
	~GameManager();
};


#endif // !_GAME_MANAGER_H