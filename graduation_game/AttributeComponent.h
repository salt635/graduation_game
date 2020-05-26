#pragma once
class AttributeComponent
{
public:
	// Stats
	int hp;
	int hpMax;
	int damage;

	AttributeComponent();
	virtual ~AttributeComponent();

	// Function
	std::string debugPrint() const;
	void updateStats(const bool reset);

	void update();
};

