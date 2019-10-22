#include "GameObject.h"


int GameObject::idCounter = 0;
bool GameObject::update(float _frameTime)
{

	return false;
}

void GameObject::draw(SDL_Renderer* _renderer)
{
	if (toAnimate)
		myAnimationManager->animate();

	myAnimationManager->draw(_renderer, myRect,flip);
	

}

void GameObject::hit()
{
}



GameObject::GameObject(SDL_Renderer* _renderer) :  isVisible(true), myTex(nullptr), toDraw(false)
{
	myAnimationManager = new animationManager();
	myAudioManager = new audioManager();

	id = idCounter;
	idCounter++;
	
}


GameObject::~GameObject()
{
	
	
}
