#pragma once

#include "MainMenuState.h"

class Game
{
private:
	// Variables
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	// 초기화
	void initVariables();	
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

public:
	// 생성자, 소멸자
	Game();
	virtual ~Game();

	// Functions

	void endApplication();

	// Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	// Render
	void render();

	void run();
};