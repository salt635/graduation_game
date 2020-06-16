#pragma once

#include "Entity.h"

class Entity;

class Player : public Entity
{
private:
	// Variable
	bool attacking;
	sf::Texture weapon_texture;
	sf::Sprite weapon_sprite;

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
	void update(const float& dt, sf::Vector2f& mouse_pos_view);

	void render(sf::RenderTarget& target);
};

