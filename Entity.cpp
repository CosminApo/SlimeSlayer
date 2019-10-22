#include "Entity.h"
#include "GameManager.h"


void Entity::attack()
{
}

void Entity::move()
{
}

void Entity::hit()
{
	hp--;
	myAudioManager->play();
	if (hp <= 0)
	{
		uiManager::incrementScore(getScoreAwarded());
		dead = true;
	}
	
}

void Entity::spawn()
{
}





std::string Entity::collision(GameObject *_obj)
{

	std::list<GameObject*>::iterator itr = GameManager::entities.begin();
	SDL_Rect *intersectionPoints = nullptr;
	
	for (; itr != GameManager::entities.end(); itr++)
	{
		
		if ((*_obj).getID() != (*itr)->getID())
		{
			bool intersection = SDL_HasIntersection(&(*_obj).getRect(), &(*itr)->getRect());
			if (intersection && (*itr)->getIsSolid())
			{
				return (*itr)->getTag();
			}
		}
	}

	return "";
}

Entity::Entity(SDL_Renderer* _renderer):GameObject(_renderer), gravityForce(1)
{
	myAudioManager->setSfx("Assets/Audio/sfx_sounds_impact1.wav");
}


Entity::~Entity()
{
}
