#include "backgroundManager.h"



void backgroundManager::update()
{
	
}

void backgroundManager::scroll()
{
}

backgroundManager::backgroundManager(SDL_Renderer* _renderer, std::string _path):GameObject( _renderer)
{
	settoDraw(true);
	myRect.h = 720;
	myRect.w = 1280;
	myRect.x = 0;
	myRect.y = 0;
	setIsSolid(false);
	setTag("Background");
	setToAnimate(false);
	myAnimationManager->initAnimator(720, 1280, _path, 0, _renderer);
}


backgroundManager::~backgroundManager()
{
}
