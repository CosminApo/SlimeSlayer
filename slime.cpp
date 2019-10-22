#include "slime.h"
#include "GameManager.h"


void slime::move(float _frameTime)
{
	
	float oldPositionX = myRect.x;
	float oldPositionY = myRect.y;

	velocityX = 0;
	velocityY = 0;

	//move towards the center of the player
	if (myRect.x < (*player).getRect().x+(*player).getRect().w/2)
	{
		setFlip(SDL_FLIP_HORIZONTAL);
		velocityX += speed;
	}

	if (myRect.x > (*player).getRect().x +(*player).getRect().w/2)
	{
		setFlip(SDL_FLIP_NONE);
		velocityX -= speed;
	}

	if (myRect.y < (*player).getRect().y + (*player).getRect().h / 2)
		velocityY += speed;

	if (myRect.y > (*player).getRect().y + (*player).getRect().h / 2)
		velocityY -= speed;
		

	myRect.x = myRect.x + (velocityX * _frameTime * 100); //movement independent of FPS
	myRect.y = myRect.y + (velocityY * _frameTime * 100);

	if (collision(this) != "" && collision(this) != "playerAttacking"   && collision(this) != "monster")
	{
		myRect.x = oldPositionX;
		myRect.y = oldPositionY;
	}
}

void slime::attack()
{
	GameObject tmpAttack = *this; //make a new temp monster
	SDL_Rect tmp = tmpAttack.getRect(); 
	tmp.w += range; //increase hitbox by range of attack
	tmp.h += range;
	if (tmp.x < (*player).getRect().x)
		tmp.x += range / 2;

	if (tmp.x > (*player).getRect().x)
		tmp.x -= range / 2;

	if (tmp.y < (*player).getRect().y)
		tmp.y += range / 2;

	if (tmp.y > (*player).getRect().y)
		tmp.y -= range / 2;


	tmpAttack.setRect(tmp); 

	if (collision(&tmpAttack) == "Player") //if new hitbox collides with player
	{
		(*player).hit(); //player is hit
	}
	//check if its behind
	if (collision(&tmpAttack) == "playerAttacking" && player->getFlip() == SDL_FLIP_NONE && myRect.x < player->getRect().x)
	{
		(*player).hit(); //player is hit
	}
	if (collision(&tmpAttack) == "playerAttacking" && player->getFlip() == SDL_FLIP_HORIZONTAL && myRect.x > player->getRect().x)
	{
		(*player).hit(); //player is hit
	}
	

}

bool slime::update(float _frameTime)
{
	bool isHit = false;
	if (!isHit)
	{
		isHit = checkIfHit();
	}
	if (isHit && feedbackTime < iframeDuration)
	{
		feedbackTime += _frameTime;
		myAnimationManager->setSpriteSheet("Assets/slime2.png", 10, 12, 14);
	}
	else
	{
		isHit = false;
		myAnimationManager->setSpriteSheet("Assets/slime1.png", 10, 12, 14);
		feedbackTime = 0;
	}
	player = findPlayer(); //target player

	if (player != nullptr)
	{
		move(_frameTime);
		attack();
	}
	
	return getDead();
}

slime::slime(SDL_Renderer* _renderer, int _posX, int _posY) :Monster(_renderer)
{
	myRect.h = 32;
	myRect.w = 32;
	myRect.x = _posX;
	myRect.y = _posY;
	velocityX = 0;
	velocityY = 0;
	setHp(3);
	feedbackTime = 0;
	setScoreAwarded(50);
	setIsSolid(true);
	setToAnimate(true);
	myAnimationManager->initAnimator(12, 14, "Assets/slime1.png", 10, _renderer);

}


slime::~slime()
{
	delete myAnimationManager;
	delete myAudioManager;
	SDL_DestroyTexture(myTex);
}
