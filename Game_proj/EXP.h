#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class EXP
{
private:
	sf::Sprite expSprite;
	sf::Texture expTexture;
	
	sf::Vector2f position;

	int type;
	float playerRange;
	float amount;

	void initVariable();
	void initSprite();

public:
	EXP(sf::Vector2f spawn_pos,int type,float amount);

	const float getAmount() const;
	const sf::FloatRect getGlobalBound() const;

	void setAmount(float amount);

	void updateExp();

	void renderExp(sf::RenderWindow& target);

};

