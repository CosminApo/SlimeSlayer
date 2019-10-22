#ifndef _PLAYER_H
#define _PLAYER_H

#include "Entity.h"
#include "GameManager.h"

class Player : public Entity
{
private:
	const float maxSpeed = 5.0f; //movement details
	const float speed = 2.5f;
	float velocityX;
	float velocityY;
	
	bool invincible; //iframes
	float timePassedIframe;
	const float iFrameDuration = 1.0f;//in seconds

public:
	void hit();
	void move(float _frameTime);
	void attack();
	bool update(float _frameTime);
	Player(SDL_Renderer* _renderer);
	~Player();
};

#endif // !_PLAYER_H