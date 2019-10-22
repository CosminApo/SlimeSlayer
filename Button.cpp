#include "Button.h"
#include "GameManager.h"


bool Button::update(float _frameTime)
{
	if (checkIfClicked())
	{
		myAudioManager->play();
		return true;
	}
	return false;
}

bool Button::checkIfClicked()
{
	bool isClicked = false;
	int x(0), y(0); 
	
	if (GameManager::Keys[SDL_BUTTON_LEFT])//if button is pressed
	{
		SDL_GetMouseState(&x, &y); //get mouse position
		//check if it is between bounds
		if (x > this->getRect().x && x < (this->getRect().x + this->getRect().w))
		{
			if (y > this->getRect().y && y < (this->getRect().y + this->getRect().h))
			{
				isClicked = true;
			}
		}
	}
	return isClicked;
}





Button::Button(SDL_Renderer* _renderer, int _x, int _y, int _h, int _w, std::string _path, std::string _tag):GameObject(_renderer)
{
	myRect.h = _h;
	myRect.w = _w;
	myRect.x = _x;
	myRect.y = _y;
	setIsSolid(false);
	setTag(_tag);
	setToAnimate(false);
	myAnimationManager->initAnimator(_h, _w, _path, 0, _renderer);
	myAudioManager->setSfx("Assets/Audio/button-pressed.wav");
}


Button::~Button()
{
	delete myAnimationManager;
	delete myAudioManager;
	SDL_DestroyTexture(myTex);
}
