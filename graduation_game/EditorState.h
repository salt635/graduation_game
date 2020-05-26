#pragma once
#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
	public State
{
private:
	// Variable
	sf::View view;

	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	sf::IntRect textureRect;
	bool collision;
	short type;
	float cameraSpeed;
	int layer;

	// Function
	void initVariables();
	void initView();
	void initBackground();
	void initFonts();
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initTileMap();
	void initGui();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();

	// Function
	void updateInput(const float& dt);
	void updateEditorInput(const float & dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};
