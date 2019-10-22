#include "GameManager.h"

std::list<GameObject*> GameManager::entities;
bool GameManager::Keys[];	
void GameManager::init(int xResolution, int yResolution)
{
	for (int i = 0; i < 322; i++) //set all keys to not pressed
	{
		Keys[i] = false;
	}
	tick = 0;
	isRunning = true;
	myWindow = nullptr;
	myRenderer = nullptr;
	int initOk = SDL_Init(SDL_INIT_EVERYTHING);
	if (initOk != 0) //init SDL
	{
		std::cout << "Unable to initialise SDL: " << SDL_GetError() << std::endl;
		isRunning = false;
	}
	else
	{
		std::cout << "SDL Initialised" << std::endl;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) //init Audio
	{
		std::cout << "Unable to initialise audio" << Mix_GetError() << std::endl;
	}
	else
	{
		std::cout << "Sound initialised" << std::endl;
	}

	if (TTF_Init() != 0) //init text
	{
		std::cout << "Unable to initialise text" << TTF_GetError() << std::endl;
	}
	else
	{
		std::cout << "Text initialised" << std::endl;
	}
	
	myWindow = SDL_CreateWindow( //init Window
		"Main",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		xResolution, yResolution,
		SDL_WINDOW_RESIZABLE);

	if (myWindow == NULL)
	{
		std::cout << "Could not create window: " << SDL_GetError << std::endl;
		isRunning = false;
	}
	else
	{
		std::cout << "Window Created" << std::endl;
	}

	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED); //init Renderer
	if (myRenderer == NULL)
	{
		std::cout << "Could not create renderer: " << SDL_GetError << std::endl;
		isRunning = false;
	}
	else
	{
		std::cout << "Renderer Created" << std::endl;
	}

	
	loadMenu();//load menu
	menuIsOpen = true;
	//loadLevel(true); //load lvl

}


void GameManager::loadEndGameScreen()
{
	myAudioManager.stopMusic();
	myAudioManager.setBgm("Assets/Audio/Deathmusic.mp3");

	entities.clear();

	entities.push_back(new backgroundManager(myRenderer, "Assets/endgameScreen.png")); //add background image
	entities.push_back(new uiManager(myRenderer,-300,300));
	menuIsOpen = true;
	entities.push_back(new Button(myRenderer, 412, 443, 107, 462, "Assets/MainMenu-button.png", "Back")); //add info button
	entities.push_back(new Button(myRenderer, 483, 579, 107, 307, "Assets/exit-button.png", "Exit")); //add exit button
	
}

void GameManager::loadMenu()
{
	myAudioManager.setBgm("Assets/Audio/08 Ascending.mp3"); //set bg music
	entities.push_back(new backgroundManager(myRenderer, "Assets/bg1.png")); //add background image
	entities.push_back(new Button(myRenderer, 412, 310, 107, 462, "Assets/start-button.png", "Start")); //add start button
	entities.push_back(new Button(myRenderer, 412, 443, 107, 462, "Assets/info-button.png", "Info")); //add info button
	entities.push_back(new Button(myRenderer, 483, 579, 107, 307, "Assets/exit-button.png", "Exit")); //add exit button
	menuIsOpen = true;
}

void GameManager::handleMenu()
{
	myAudioManager.play();
	std::list<GameObject*>::iterator itr = entities.begin();
	bool isClicked = false;
	while (itr != entities.end())
	{
		isClicked = (*itr)->update(0); //itr is a pointer to a pointer > dereference required
		if (isClicked)
		{
			if ((*itr)->getTag() == "Start")//if its the start button 
			{
				entities.clear(); //remove all buttons
				myAudioManager.stopMusic(); //stop music
				menuIsOpen = false; //close menu
				loadLevel(true); // load first level
				break;
			}
			else if ((*itr)->getTag() == "Exit")//if its exit button
			{
				isRunning = false; //quit the game
			}
			else if ((*itr)->getTag() == "Back" )//if its back button
			{
				entities.clear(); //clear the info menu
				myAudioManager.stopMusic();
				loadMenu(); //reload the menu
				break;
			}
			else if ((*itr)->getTag() == "Info")//if its info button
			{
				entities.clear(); //remove the current menu
				entities.push_back(new backgroundManager(myRenderer, "Assets/Info.png")); //add info image
				entities.push_back(new Button(myRenderer, 981, 614, 98, 294, "Assets/back-button.png", "Back"));
				break;

			}
		}
		itr++;
	}
}


void GameManager::HandleEvents()
{

	while (SDL_PollEvent(&Event)) {
		switch (Event.type) {

		case SDL_QUIT:
			isRunning = false; //close game if you quit
			break;
		case SDL_KEYDOWN:
			if (Event.key.keysym.sym >= 0 && Event.key.keysym.sym < 322 && isPlayerAlive)
			Keys[Event.key.keysym.sym] = true; //if a key is pressed set it to true
			break;
		case SDL_KEYUP:
			if (Event.key.keysym.sym >= 0 && Event.key.keysym.sym < 322 && isPlayerAlive)
			Keys[Event.key.keysym.sym] = false; //if a key is released set it to false
			break;
		case SDL_MOUSEBUTTONDOWN:
			Keys[Event.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			Keys[Event.button.button] = false;
			break;
		default:
			break;
		}
	}
}

int GameManager::update()
{
	monsterCount = countEntitiesWithTag("monster"); //count how many monsters there are
	if (monsterCount <= 0) //if no more monsters left
	{
		nextLevel(); //goto next level
	}
	float frameTime = (SDL_GetTicks() - tick) / 1000.0f; // get time between frams

	// Clamp maximum delta time value
	if (frameTime > 0.05f)
	{
		frameTime = 0.05f;
	}

	tick = SDL_GetTicks(); //keep track of current tick

	std::list<GameObject*>::iterator itr = entities.begin();
	bool isDestroyed = false;
	while (itr != entities.end())
	{
		isDestroyed = (*itr)->update(frameTime); //itr is a pointer to a pointer > dereference required
		if (isDestroyed)
		{
			if ((*itr)->getTag() == "Player" || (*itr)->getTag() == "playerAttacking")//if the player died
			{
				isPlayerAlive = false;
				loadEndGameScreen();
				return 0;
			}
			if ((*itr)->getTag() != "Explosion")//if its not an explosion
			{
				entities.push_back(new Explosion(myRenderer, (*itr)->getRect().x, (*itr)->getRect().y)); //play death animation

			}
		
			itr = entities.erase(itr);
	
		}
		else
		{
			++itr;
		}
	}

	return 0;
}

void GameManager::render()
{

	std::list<GameObject*>::iterator itr = entities.begin();

	for (; itr != entities.end(); itr++)
	{
		if ((*itr)->getIsVisible()) //only draw if it is visible
			(*itr)->draw(myRenderer); //itr is a pointer to a pointer > dereference required


	}
	SDL_RenderPresent(myRenderer);
	SDL_RenderClear(myRenderer);

}

void GameManager::clean()
{
	//clean up all memory
	SDL_DestroyRenderer(myRenderer);
	SDL_DestroyWindow(myWindow);
	Mix_CloseAudio();
	TTF_Quit();

}

void GameManager::loadLevel(bool _isFirst) 
{
	uiManager::incrementLevel(1); //increment Current level
	srand(time(NULL));
	//elements are layered based on the order they are drawn in (first object = background)
	int noOfSlimes = level + 1 * 2; //add monsters to the level based on current level (increase in difficulty)
	int noOfSkeletals = level * 0.5;

	if (_isFirst) //if its the first level
	{
		entities.push_back(new backgroundManager(myRenderer, "Assets/bg2.png")); //add background.
		entities.push_back(new Player(myRenderer)); //add player
	}
	for (int j = 0; j < noOfSlimes; j++)
	{
																				//randNum = rand()%(max-min + 1) + min;
		entities.push_back(new slime(myRenderer, rand() % (1102-161+1)+161, rand() % (554-125+1)+125)); //spawn new slime at random spot on the map
		monsterCount++;//increase monster count
	}

	if (_isFirst)
	{
		isPlayerAlive = true;
		uiManager::setLevel(0);
		uiManager::setScore(0);
		level = 0;

		myAudioManager.setBgm("Assets/Audio/05 Come and Find Me.mp3"); //set bg music
		myAudioManager.play();
		//create arena boundaries
		entities.push_back(new Platform(myRenderer, 73, 607, 1146, 56)); //add platform
		entities.push_back(new Platform(myRenderer,65,67, 1146,56)); //add platform
		entities.push_back(new Platform(myRenderer, 72, 72, 49, 572)); //add platform
		entities.push_back(new Platform(myRenderer, 1173, 58, 49, 572)); //add platform
		entities.push_back(new uiManager(myRenderer,0,0)); //add ui

	}
	myAudioManager.play(); //start the music


	
}

int GameManager::countEntitiesWithTag(std::string _tag)
{
	int count = 0;
	std::list<GameObject*>::iterator itr = entities.begin();
	for (; itr != entities.end(); itr++)
	{
		if ((*itr)->getTag() == _tag) //if itr has the tag required
		count++; //increment the count
	}
	return count;
}

void GameManager::nextLevel()
{
	level++;
	loadLevel(false);
}

GameManager::GameManager()
{
}


GameManager::~GameManager()
{
}
