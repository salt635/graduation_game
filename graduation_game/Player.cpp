#include "stdafx.h"
#include "Player.h"

// Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	
}

// 持失切, 社瑚切
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 16.f, 50.f, 48.f, 58.f);
	this->createMovementComponent(350.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 64, 108);
	this->animationComponent->addAnimation("WALK", 10.f, 4, 0, 7, 0, 64, 108);
	this->animationComponent->addAnimation("ATTACK", 8.f, 8, 0, 8, 0, 64, 108);
}

Player::~Player()
{

}

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float & dt)
{
	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(80.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}

		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	//else if (this->movementComponent->getState(JUMP))
	//{

	//}
}

//Functions
void Player::update(const float & dt)
{
	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}
