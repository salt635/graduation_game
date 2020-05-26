#pragma once

#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	// Variable
	bool attacking;

	// Initializer function
	void initVariables();
	void initComponents();

public:
	Player(float x, float y, sf::Texture& texture_sheet);
	virtual ~Player();
	
	// Accessor
	AttributeComponent* getAttributeComponent();

	// Function
	void loseHP(const int hp);
	void gainHP(const int hp);
	void updateAttack();
	void updateAnimation(const float& dt);
	void update(const float& dt);

	void render(sf::RenderTarget& target);
};

