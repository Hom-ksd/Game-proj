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

class Bullet
{
private:
	//Variable
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;

	//Bullet logic
	int heigth;
	int width;
	sf::IntRect bulletRect;
	int animateCnt;
	float bulletRotation;
	float bulletSpeed;
	sf::Vector2f direction;

	//delay animate bullet;
	sf::Clock clock;
	sf::Time time;

	//Private functiom
	void initVariable();
	void initBulletSprite();
	void iniitbulletDir();

public:
	Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y,float rotation);

	const sf::FloatRect getBounds() const;
	const sf::Vector2f getPos() const;

	void setScale(float x, float y);

	//update bullet
	void updateBulletAnimation();
	void updateBulletPos();
	void updateBullet();

	//render bullet
	void renderBullet(sf::RenderWindow& target);
};

