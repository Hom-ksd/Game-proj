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

class AboutMenu
{
private:
	sf::Font font;
	sf::Text menu[maxItem]; // Start , Leader baord , about , exit

	int selectedItem;

public:
	AboutMenu(float width, float height);
	~AboutMenu();

	void MoveUp();
	void MoveDown();

	const int getPressedItem() const;

	void setPos(float posx, float posy);

	void renderMenu(sf::RenderWindow& window);
};

