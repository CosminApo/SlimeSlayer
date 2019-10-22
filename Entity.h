#ifndef _ENTITY_H
#define _ENTITY_H 

#include <list>
#include "GameObject.h"


class Entity : public GameObject
{
private:
	int hp;
	int power;
	bool isFalling;
	bool dead;
	const float gravityForce;
	int scoreAwarded;
public:
	void setScoreAwarded(int _score) { scoreAwarded = _score; }
	int getScoreAwarded() { return scoreAwarded; }
	virtual void attack();
	virtual void move();
	virtual void hit();
	void spawn();
	std::string collision(GameObject *_obj);
	void setHp(int _hp) { hp = _hp; }
	int getHp() { return hp; }
	void setDead(int _dead) { dead = _dead; }
	bool getDead() { return dead; }
	
	void setIsFalling(bool _isFalling) { isFalling = _isFalling; }
	Entity(SDL_Renderer* _renderer); 
	~Entity();
};

#endif //!_ENTITY_H