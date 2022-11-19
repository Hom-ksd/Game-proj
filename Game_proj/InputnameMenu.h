#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class InputnameMenu
{
private:
	sf::Font font;
	sf::Text name;
	sf::Text textbox;
	std::ostringstream text;
	bool isEnter;
	int limit;

	void initfont();
	void inputLogic(int charType);
	void delLastChar();


public:
	InputnameMenu(float width, float height);

	void typedOn(sf::Event input);
	void setPos(float posx, float posy);

	const sf::Vector2f getPos() const;
	const bool getEnter() const;
	const std::string getName() const;
	void resetEnter();

	void renderTextBox(sf::RenderWindow& target);
};

