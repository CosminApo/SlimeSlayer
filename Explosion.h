#ifndef _EXPLOSION_H
#define	_EXPLOSION_H

#include "Entity.h"
class Explosion : public Entity
{
private:
	float tick;
	float startTime;
	float const duration = 0.7f; //in seconds
public:
	bool update(float _frameTime);
	Explosion(SDL_Renderer* _renderer, int _x, int _y);
	~Explosion();
};

#endif // !_EXPLOSION_H