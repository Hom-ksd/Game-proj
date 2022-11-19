#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Tile.h"
class TileMap
{
private:
	float gridSizeF;
	unsigned gridSizeU;
	unsigned layers;
	sf::Texture *texture;
	std::map<std::string, sf::Texture*> tileset;
	sf::Vector2u maxSize;
	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::Texture tileTextureSheet;

	void initTilemap();
	void addTile();

public:
	TileMap();

	
	//render
	void renderTilemap(sf::RenderTarget& target,sf::Vector2i playerPos,sf::Vector2f viewSize);
};

