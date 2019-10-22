#ifndef _BUTTON_H
#define _BUTTON_H

#include "GameObject.h"
class Button :	public GameObject
{
private:

public:
	bool update(float _frameTime);
	bool checkIfClicked();
	Button(SDL_Renderer* _renderer, int _x, int _y, int _h, int _w, std::string _path, std::string _tag);
	~Button();
};

#endif //! _BUTTON_H