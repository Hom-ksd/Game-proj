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



class Wands
{
private:
	//Variable
	sf::Texture wandTexture;
	sf::Sprite wandSprite;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	//Wand Logic 
	int wandsLvl;
	float wandsExp;
	float wandExpCapPerLvl[12];
	int heigth;
	int width;
	int windowHeigth;
	int windowWidth;
	int playerHeigth;
	int playerWidth;
	sf::IntRect wandRect;
	float rotation;
	sf::Vector2f direction;
	// Wand Level start at 0 to 12 = 13 levels

	//private function
	void initVariable();
	void initWandTexture();
	void initWandSprite();

public:
	Wands();

	void addWandLvl(float amount);

	//update Wand
	void updateWandLevel();
	void updateWandSprite();
	void updateMousePos(sf::RenderWindow& target);
	void updateWandTarget(int playerPosX, int playerPosY);
	void updateWandPos(int playerPosX, int playerPosY);
	void updateWand(sf::RenderWindow& target, sf::Vector2i playerPos);

	//return value
	float returnWandTarget();
	sf::Vector2f returnWandDirection();
	const int getWandLvl() const; 
	const float getMaxWandExp() const;
	const float getWandExp() const;

	//render Wand 
	void renderWand(sf::RenderWindow& target);
};