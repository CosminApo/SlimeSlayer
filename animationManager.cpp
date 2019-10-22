#include "animationManager.h"



animationManager::animationManager()
{
}


animationManager::~animationManager()
{
	SDL_DestroyTexture(myTex);
}

bool animationManager::initAnimator(int _spriteHeight, int _spriteWidth, std::string _spriteSheet, int _frames, SDL_Renderer* _renderer)
{

	spriteHeight = _spriteHeight;
	spriteWidth = _spriteWidth;
	spriteSheet = _spriteSheet;
	frames = _frames;
	currentSprite.h = spriteHeight;
	currentSprite.w = spriteWidth;

	
	return true;
}

void  animationManager::createTexture(SDL_Renderer* _renderer)
{
	SDL_Surface* tmpsurf = IMG_Load(spriteSheet.c_str());
	if (tmpsurf == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << "\n";
	}
	myTex = SDL_CreateTextureFromSurface(_renderer, tmpsurf);
	SDL_FreeSurface(tmpsurf);

}

void animationManager::animate()
{
	currentSprite.x = spriteWidth * (int)((SDL_GetTicks() / speed) % frames);
}
void animationManager::setSpriteSheet(std::string _spriteSheet, int _frames, int _spriteHeight, int _spriteWidth)
{
	spriteSheet = _spriteSheet;
	frames = _frames;
	spriteHeight = _spriteHeight;
	spriteWidth = _spriteWidth;
	currentSprite.h = spriteHeight;
	currentSprite.w = spriteWidth;
	currentSprite.x = 0;
}
void animationManager::draw(SDL_Renderer* _renderer, SDL_Rect _myRect, SDL_RendererFlip _flip)
{
	
	createTexture(_renderer);
	SDL_RenderCopyEx(_renderer, myTex, &currentSprite, &_myRect,0,0, _flip);
	SDL_DestroyTexture(myTex);
	
}
