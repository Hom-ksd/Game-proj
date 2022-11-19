#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#define maxItem 6

class LeaderMenu
{
private:
	sf::Font font;
	sf::Text menu[maxItem]; // Start , Leader baord , about , exit
	std::fstream Leader;
	int selectedItem;
	std::string ldata[5];
	std::vector<std::pair<int, std::string>> data;
	void initFile();

public:
	LeaderMenu(float width, float height);
	~LeaderMenu();

	void addData(std::string name, int score);
	void updateData();
	void updateString();

	const int getPressedItem() const;

	void setPos(float posx, float posy);

	void renderMenu(sf::RenderWindow& window);
};

