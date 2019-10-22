#ifndef _BACKGROUND_MANAGER_H
#define _BACKGROUND_MANAGER_H

#include "GameObject.h"

class backgroundManager : public GameObject
{
public:
	void update();
	void scroll();
	backgroundManager(SDL_Renderer* _renderer, std::string _path);
	~backgroundManager();
};

#endif // !_BACKGROUND_MANAGER_H