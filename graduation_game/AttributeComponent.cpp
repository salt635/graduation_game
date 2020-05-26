#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent()
{
	this->damage = 1;
	this->hp = 6;
	this->hpMax = 6;
}

AttributeComponent::~AttributeComponent()
{

}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Hp: " << this->hp << "\n"
		<< "HpMax: " << this->hpMax << "\n"
		<< "Dmg: " << this->damage << "\n";

	return ss.str();
}

// Function
void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax = 6;

	if (reset)
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::update()
{
}
