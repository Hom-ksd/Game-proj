#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define maxItem 3

class PauseMenu
{
private:
	sf::Font font;
	sf::Text menu[maxItem]; // Start , Leader baord , about , exit
	sf::Text TextDie;
	int selectedItem;

public:
	PauseMenu(float width, float height);

	void MoveUp();
	void MoveDown();

	const int getPressedItem() const;
	const sf::Vector2f getPos() const;

	void setPos(float posx, float posy);

	void renderMenu(sf::RenderWindow& window);
};

