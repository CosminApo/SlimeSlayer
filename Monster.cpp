#include "Monster.h"
#include "GameManager.h"

GameObject* Monster::player;

GameObject* Monster::findPlayer()
{
	std::list<GameObject*>::iterator itr = GameManager::entities.begin();
	GameObject *player = nullptr;
	bool found = false;

	for (; itr != GameManager::entities.end(); itr++) //loop through all objects
	{
		if ((*itr)->getTag() == "Player" || (*itr)->getTag() == "playerAttacking") //find the one tagged player
		{
			found = true;
			player = (*itr); //set player 
		}
	}
	if (found)
	{
		return player;
	}
	else //ERROR
		return nullptr;
}

void Monster::move()
{
}

void Monster::attack()
{
}

bool Monster::checkIfHit()
{
	if (collision(this) == "playerAttacking")
	{
		//push back if hit
		SDL_Rect temp = this->getRect();
		if (temp.x < player->getRect().x)
			temp.x -= 30;
		if (temp.x > player->getRect().x)
			temp.x += 30;
		this->setRect(temp);

		hit();
		return true;
	}
	return false;
}

Monster::Monster(SDL_Renderer* _renderer) :Entity(_renderer)
{
	setTag("monster");

}


Monster::~Monster()
{
}
