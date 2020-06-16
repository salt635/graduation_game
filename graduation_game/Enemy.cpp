#include "stdafx.h"
#include "Enemy.h"

// Initializer functions
void Enemy::initVariables()
{
	
}

void Enemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 64, 108);
	this->animationComponent->addAnimation("WALK", 10.f, 4, 0, 7, 0, 64, 108);
	this->animationComponent->addAnimation("ATTACK", 8.f, 8, 0, 8, 0, 64, 108);
}

// 持失切, 社瑚切
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 16.f, 50.f, 48.f, 58.f);
	this->createMovementComponent(350.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent();

	this->initAnimations();
}

Enemy::~Enemy()
{

}

void Enemy::update(const float & dt, sf::Vector2f& mouse_pos_view)
{
	this->attributeComponent->update();

	this->movementComponent->update(dt);

	//this->updateAttack();

	//this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
