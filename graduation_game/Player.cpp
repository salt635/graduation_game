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
	this->createMovementComponent(350.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent();

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 64, 108);
	this->animationComponent->addAnimation("WALK", 10.f, 4, 0, 7, 0, 64, 108);
	this->animationComponent->addAnimation("ATTACK", 8.f, 8, 0, 8, 0, 64, 108);

	this->weapon_texture.loadFromFile("Resources/Images/Sprites/Player/bow.png");
	this->weapon_sprite.setTexture(this->weapon_texture);
	this->weapon_sprite.setOrigin(
		this->weapon_sprite.getGlobalBounds().width - 64.f,
		this->weapon_sprite.getGlobalBounds().height / 2.f
	);
}

Player::~Player()
{
	
}

AttributeComponent * Player::getAttributeComponent()
{
	return this->attributeComponent;
}

// Function
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
	{
		this->attributeComponent->hp = 0;
	}
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
	{
		this->attributeComponent->hp = this->attributeComponent->hpMax;
	}
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
}

void Player::update(const float & dt, sf::Vector2f& mouse_pos_view)
{
	this->attributeComponent->update();

	this->movementComponent->update(dt);

	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	// Weapon
	this->weapon_sprite.setPosition(this->getCenter());
	// Rotate weapon
	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.141592;
	float deg = atan2(dY, dX) * 180 / PI;

	this->weapon_sprite.setRotation(deg);
}

void Player::render(sf::RenderTarget & target)
{
	target.draw(this->sprite);
	target.draw(this->weapon_sprite);

	this->hitboxComponent->render(target);
}
