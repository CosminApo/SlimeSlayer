#include "uiManager.h"




int uiManager::hp;
int uiManager::score;
int uiManager::level;
bool uiManager::update(float _frameTime)
{

	return false; //don't destroy it
}

void uiManager::draw(SDL_Renderer* _renderer)
{
	drawScore();
	drawHp();
	drawLvl();
}

void uiManager::setScore(int _score)
{
	score = _score;
}

void uiManager::setLevel(int _level)
{
	level = _level;
}

void uiManager::setHp(int _hp)
{
	hp = _hp;
}

void uiManager::drawScore()
{
	text = "Score " + std::to_string(score);
	textpos->x = xStartingPoint + 908; //set where to display the text
	textpos->y = yStartingPoint + 0;
	textpos->w = 361;
	textpos->h = 51;
	surface = TTF_RenderText_Solid(font, text.c_str(), color); //set the text
	texture = SDL_CreateTextureFromSurface(renderer, surface); //create the text
	SDL_RenderCopy(renderer, texture, NULL, textpos); //copy the text to the renderer
}

void uiManager::drawHp()
{
	//draw a heart for each hp
	textpos->x = xStartingPoint + 0;
	textpos->y = yStartingPoint + 0;
	textpos->w = 64;
	textpos->h = 64;
	surface = IMG_Load("Assets/heart pixel art.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	for (int i = 0; i < hp; i++)
	{
		textpos->x = textpos->w*i;
		SDL_RenderCopy(renderer, texture, NULL, textpos);
	}
	

}

void uiManager::drawLvl()
{
	text = "LVL: " + std::to_string(level);
	textpos->x = xStartingPoint+586;
	textpos->y = yStartingPoint+0;
	textpos->w = 122;
	textpos->h = 51;
	surface = TTF_RenderText_Solid(font, text.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_RenderCopy(renderer, texture, NULL, textpos);
}

uiManager::uiManager(SDL_Renderer* _renderer, int _xStartingPoint, int _yStartingPoint ) : GameObject(_renderer)
{

	xStartingPoint = _xStartingPoint;
	yStartingPoint = _yStartingPoint;
	textpos = new SDL_Rect();
	renderer = _renderer;
	font = TTF_OpenFont("Assets/The Wild Breath of Zelda.otf", 25);
	if (font == nullptr)
	{
		std::cout << "Error opening font" << std::endl;
	}
	setIsVisible(true);
	setTag("UI");
	text = "";
}


uiManager::~uiManager()
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
