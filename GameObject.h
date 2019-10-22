#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H

#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include <iostream>
#include "animationManager.h"
#include "audioManager.h"


class GameObject
{
protected:
	SDL_Rect myRect; //size and position of object
	animationManager* myAnimationManager;
	audioManager* myAudioManager;
	SDL_Texture* myTex; //sprite of object
private: 
	bool toDraw;
	bool isVisible;
	bool isSolid;
	bool toAnimate;
	std::string tag;
	SDL_RendererFlip flip;
	int id;
	//animation components
	int spriteHeight;
	int spriteWidth;
public:
	static int idCounter; //used to generate new ID

	virtual bool update(float _frameTime);
	virtual void draw(SDL_Renderer* _renderer);
	virtual void hit(); //necessary for attacks

	void setTag(std::string _tag) { tag = _tag; }
	void setIsSolid(bool _isSolid) { isSolid = _isSolid; }
	void settoDraw(bool _toDraw) { toDraw = _toDraw; }
	void setID(int _id) { id = _id; }
	void setRect(SDL_Rect _rect) { myRect = _rect; }
	void setIsVisible(bool _isVisible) { isVisible = _isVisible; }
	void setToAnimate(bool _toAnimate) { toAnimate = _toAnimate; }
	void setFlip(SDL_RendererFlip _flip) { flip = _flip; }
	
	bool getIsVisible() { return isVisible; }
	bool getToAnimate() { return toAnimate; }
	SDL_RendererFlip getFlip() { return flip; }
	int getID() { return id; }
	SDL_Rect getRect() { return myRect; }
	bool gettoDraw() { return toDraw; }
	std::string getTag() { return tag; }
	bool getIsSolid() { return isSolid; }

	GameObject(SDL_Renderer* _renderer);
	~GameObject();
};

#endif // !_GAME_OBJECT_H