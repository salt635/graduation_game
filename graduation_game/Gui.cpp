#include "stdafx.h"
#include "Gui.h"

gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(36);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->shape.setFillColor(this->idleColor);
}

gui::Button::~Button()
{

}

// Accessors
const bool gui::Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
		return true;

	return false;
}

const std::string& gui::Button::getText() const
{
	return this->text.getString();
}

// Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

// Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hove and pressed*/

	// Idle
	this->buttonState = BTN_IDLE;

	// Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor);
		break;

	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor);
		break;

	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor);
		break;

	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}

// DropDownList ==================================================
gui::DropDownList::DropDownList(sf::Font& font, std::string list[], unsigned numOfElements, unsigned defalt_index)
	:font(font)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	for (size_t i = 0; i < numOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				840.f, 650.f, 240.f, 70.f,
				&this->font, list[i],
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200),
				sf::Color(20, 20, 20, 200)
			)
		);
	}

	this->activeElement = new Button(*this->list[defalt_index]);
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (auto *&i : this->list)
		delete i;
}

void gui::DropDownList::update(const sf::Vector2f & mousePos)
{

}

void gui::DropDownList::render(sf::RenderTarget & target)
{

}
