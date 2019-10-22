#ifndef _MONSTER_H

#define _MONSTER_H

#include "Entity.h"

class Monster :	public Entity
{
protected:
	static GameObject* player;
public:
	GameObject* findPlayer();
	virtual void move();
	virtual void attack();
	bool checkIfHit();
	Monster(SDL_Renderer* _renderer);
	~Monster();
};
#endif // !_MONSTER_H
