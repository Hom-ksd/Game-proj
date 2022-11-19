#pragma once


#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <math.h>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Foods
{
private:
	std::stringstream ss;
	sf::Sprite foodSprite;
	sf::Texture foodTexture;
	
	float healAmount;

	sf::Vector2f spawn_pos;

	void initVariable();
	void initSprite();

public:
	Foods(sf::Vector2f spawn_pos);

	const sf::FloatRect getGlobalBounds() const;
	const float getHealAmount() const;

	void updateFood();

	void renderFood(sf::RenderWindow& target);
};

