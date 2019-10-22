#ifndef _SLIME_H

#define _SLIME_H

#include "Monster.h"

class slime : public Monster
{
private:
	const float speed = 1;
	float velocityX;
	float velocityY;
	float feedbackTime;
	const float iframeDuration = 1000;
	const float range = 8;
public:
	void move(float _frameTime);
	void attack();
	bool update(float _frameTime);
	slime(SDL_Renderer* _renderer, int _posX, int _posY);
	~slime();
};

#endif // !_SLIME_H