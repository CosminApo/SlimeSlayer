#ifndef _ANIMATION_MANAGER_H

#define _ANIMATION_MANAGER_H
#include "SDL.h"
#include <string>
#include "SDL_image.h"
#include <iostream>

class animationManager
{
private:
	SDL_Texture* myTex; //the texture of the file
	const int speed = 80; //determines frame per second
	int spriteHeight; //sprite details
	int spriteWidth;
	std::string spriteSheet; //path to the sprite sheet
	int frames; // frames per sprite sheet
	SDL_Rect currentSprite; //rect to indicate current sprite

public:
	bool initAnimator(int _spriteHeight, int _spriteWidth, std::string _spriteSheet, int _frames, SDL_Renderer* _renderer);
	void createTexture(SDL_Renderer* _renderer);
	void animate();
	void setSpriteSheet(std::string _spriteSheet, int _frames, int _spriteHeight, int _spriteWidth);
	void draw(SDL_Renderer* _renderer, SDL_Rect _myRect, SDL_RendererFlip _flip);
	void setFrames(int _frames) { frames = _frames; }
	animationManager();
	~animationManager();
};
#endif // ! _ANIMATION_MANAGER_H
