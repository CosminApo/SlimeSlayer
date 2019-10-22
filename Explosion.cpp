#include "Explosion.h"



bool Explosion::update(float _frameTime)
{	
	startTime += _frameTime;
	if (startTime > duration)
	{
		return true;
	}
	return false;
}

Explosion::Explosion(SDL_Renderer* _renderer, int _x, int _y) :Entity(_renderer)
{
	tick = 0;
	myRect.h = 32;
	myRect.w = 32;
	myRect.x = _x;
	myRect.y = _y;
	setIsSolid(false);
	setTag("Explosion");
	setToAnimate(true);
	myAnimationManager->initAnimator(96, 96, "Assets/Explosion.png", 12, _renderer);
	myAudioManager->setSfx("Assets/Audio/sfx-explosion-15.wav"); 
	startTime = 0;
	myAudioManager->play();
	setIsVisible(true);
}


Explosion::~Explosion()
{

}
