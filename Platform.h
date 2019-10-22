#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "GameObject.h"
class Platform : public GameObject
{

public:
	Platform(SDL_Renderer * _renderer, int _x, int _y, int _width, int _height);
	~Platform();
};

#endif