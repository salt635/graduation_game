#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

namespace gui
{
	class Button
	{
	private:
		short unsigned buttonState;

		sf::RectangleShape shape;
		sf::Font* font;
		sf::Text text;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text,
			sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
		~Button();

		// Accessor
		const bool isPressed() const;
		const std::string& getText() const;

		// Modifier
		void setText(const std::string text);

		// Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;

	public:
		DropDownList(sf::Font& font, std::string list[], unsigned numOfElements, unsigned defalt_index);
		~DropDownList();

		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};
}