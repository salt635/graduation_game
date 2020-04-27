#include "stdafx.h"
#include "MovementComponent.h"

// Init
MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite), maxVelocity(maxVelocity),
	acceleration(acceleration), deceleration(deceleration)
{
	
}

MovementComponent::~MovementComponent()
{

}

const sf::Vector2f & MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float & MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const bool MovementComponent::getState(const short unsigned state) const
{
	switch (state)
	{
	case IDLE:
		if (this->velocity.x == 0.f && this->velocity.y == 0.f)
			return true;
		break;

	case MOVING:
		if (this->velocity.x != 0.f || this->velocity.y != 0.f)
			return true;
		break;

	case MOVING_LEFT:
		if (this->velocity.x < 0.f)
			return true;
		break;

	case MOVING_RIGHT:
		if (this->velocity.x > 0.f)
			return true;
		break;
	case MOVING_UP:
		if (this->velocity.y < 0.f)
			return true;
		break;

	case MOVING_DOWN:
		if (this->velocity.y > 0.f)
			return true;
		break;
	}
	return false;
}

// Functions
void MovementComponent::move(const float x, const float y, const float& dt)
{
	/* sprite가 최대 속도에 도달할 때까지 가속. */
	
	this->velocity.x += this->acceleration * x;
	this->velocity.y += this->acceleration * y;
}

void MovementComponent::update(const float & dt)
{
	/* 
		sprite를 감속하고 최대속도 제어.
		sprite를 이동시킨다.
	*/

	if (this->velocity.x > 0.f) // Check for positive x
	{
		// Max velocity check
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		// Deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
			this->velocity.x = 0.f;
	}
	else if (this->velocity.x < 0.f) // Check for negative x
	{
		// Max velocity check
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		// Deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
			this->velocity.x = 0.f;
	}

	if (this->velocity.y > 0.f) // Check for positive y
	{
		// Max velocity check
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		// Deceleration
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
			this->velocity.y = 0.f;
	}
	else if (this->velocity.y < 0.f) // Check for negative y
	{
		// Max velocity check
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		// Deceleration
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
			this->velocity.y = 0.f;
	}

	// Use velocity
	this->sprite.move(this->velocity * dt);
}