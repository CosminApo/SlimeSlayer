#include "Player.h"
#include "GameManager.h"


void Player::hit()
{
	if (!invincible)
	{
		Entity::hit(); //call the base class hit function
		invincible = true;
		uiManager::incrementHp(-1);
	}

}

void Player::move(float _frameTime)
{
	float oldPositionX = myRect.x;
	float oldPositionY = myRect.y;
	
	float velocityX = 0;
	float velocityY = 0;


	if (GameManager::Keys[SDLK_w]) //move up
	{
		if (velocityY < maxSpeed)
		{
			velocityY -= speed;
		}
	}



	if (GameManager::Keys[SDLK_a])  //move left
	{
		setFlip(SDL_FLIP_HORIZONTAL); //mirror the image
		if (velocityX < maxSpeed)
		{
			velocityX -= speed;
		}
	}


	if (GameManager::Keys[SDLK_s]) //move down
	{
		if (velocityY < maxSpeed)
		{
			velocityY += speed;
		}
	}


	if (GameManager::Keys[SDLK_d])  //move right
	{
		setFlip(SDL_FLIP_NONE); //mirror the image
		if (velocityX < maxSpeed)
		{
			velocityX += speed;
		}
	}

	if (velocityX > maxSpeed) //clamp velocity
		velocityX = maxSpeed;

	if (velocityY > maxSpeed) //clamp velocity
		velocityY = maxSpeed;



	myRect.x = myRect.x + (velocityX * _frameTime*100);
	myRect.y = myRect.y + (velocityY * _frameTime*100);
	if (myRect.x != oldPositionX || myRect.y != oldPositionY)
	{
		myAnimationManager->setSpriteSheet("Assets/playerRun2.png",6,21,27);
	}
	else
	{
		myAnimationManager->setSpriteSheet("Assets/playerIdle6.png",4,28,27);
	}
	if (collision(this) != "")
	{
		myRect.x = oldPositionX;
		myRect.y = oldPositionY;
	}

}

void Player::attack()
{
	bool hasAttacked = false;
	if (GameManager::Keys[SDL_BUTTON_LEFT])
	{
		hasAttacked = true;
		setTag("playerAttacking");

	}
	if (!GameManager::Keys[SDL_BUTTON_LEFT])
	{
		setTag("Player");
	}
	if (hasAttacked)
	{
		myAnimationManager->setSpriteSheet("Assets/playerAttack2.png", 15, 21, 27);
	}
}



bool Player::update(float _frameTime)
{
	uiManager::setHp(getHp());
	if (invincible)
	{
		timePassedIframe += _frameTime; //increment time passed since iframe started
		setIsVisible(!getIsVisible()); //flash on screen
	}
	if (timePassedIframe > iFrameDuration ) //if more time passed than the duration
	{
		//end iframes
		timePassedIframe = 0;
		invincible = false; 
	}

	move(_frameTime);
	attack();
	return getDead();
}

Player::Player(SDL_Renderer* _renderer) :Entity(_renderer)
{
	settoDraw(true);
	myRect.h = 64;
	myRect.w = 64;
	myRect.x = 1280/2;
	myRect.y = 720/2;
	velocityX = 0;
	velocityY = 0;
	invincible = false;
	setHp(3);

	setScoreAwarded(0); //could be changed so that player on death receives score based on level reached
	setTag("Player");
	setIsSolid(true);
	setToAnimate(true);
	myAnimationManager->initAnimator(28, 27, "Assets/playerIdle6.png", 4, _renderer);
	myAudioManager->setSfx("Assets/Audio/sfx_sounds_impact2.wav");

	setIsFalling(true);
}


Player::~Player()
{
	delete myAnimationManager;
	delete myAudioManager;
	SDL_DestroyTexture(myTex);
}
