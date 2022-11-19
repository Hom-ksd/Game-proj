#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Tile
{
private:
	//variable
	sf::RectangleShape shape;
	int heigth;
	int width;
	sf::Texture *texture;
	
	void initVariable();
	
public:
	Tile(float pos_x, float pos_y, float gridSizeF, sf::Texture& texture, sf::IntRect textureRect);

	void renderTile(sf::RenderTarget& target);

	const sf::Vector2f getTilePos() const;
};

