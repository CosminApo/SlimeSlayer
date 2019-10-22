#include "Platform.h"



Platform::Platform(SDL_Renderer* _renderer, int _x, int _y, int _width, int _height) :GameObject(_renderer)
{
	settoDraw(true);
	myRect.h = _height;
	myRect.w = _width;
	myRect.x = _x;
	myRect.y = _y;
	setIsSolid(true);
	setTag("platform");
	setToAnimate(false);
	setIsVisible(false);

	
}


Platform::~Platform()
{
}
