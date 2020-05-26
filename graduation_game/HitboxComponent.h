#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	virtual ~HitboxComponent();

	// Accessor
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBoudns() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	// Modifier
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	// Function
	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};
