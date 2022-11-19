#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Enemies
{
private:
	//Variable
	sf::RectangleShape shape;
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	sf::IntRect enemyRect;
	
	//logic Enemies
	float health;
	float maxHealth;
	float spawn_x;
	float spawn_y;
	sf::Vector2f viewSize;
	float width;
	float heigth;
	float walkSpeed;
	
	bool isDead;
	bool checkisdead;
	bool isInPlayerRange;
	sf::Clock deadClock;
	sf::Time deadTime;

	bool isTurnLeft;
	bool isWalk;
	bool isAtk;
	sf::Vector2f moveEnemy;
	sf::Vector2f originPoint;
	sf::Vector2f playerPos;
	float normalizeSpeed;
	float playerRange;

	bool atkState;

	//animation
	sf::Clock clock;
	sf::Time time;
	sf::Clock atkClock;
	sf::Time atkTime;
	sf::Vector2i index_idle;
	sf::Vector2i index_atk;
	sf::Vector2i index_walk;
	sf::Vector2i index_die;
	sf::Vector2i index_dmg;
	

	//function
	void initVariable();
	void initEnemySprite();

public:
	Enemies(sf::Texture* texture,float pos_x,float pos_y,float HP,float DMG);

	sf::Clock delayDmg;
	sf::Time timeDmg;
	float enemyDmg;

	float score;

	//public function 
	const sf::Vector2f getEnemyPos() const;
	const float getEnemyHealth() const;
	const float getEnemyMaxHealth() const;
	const bool getEnemyState() const;
	const sf::FloatRect getBounds() const;
	void damageEnemy(float amount);
	const bool getEnemyAtk() const;


	//update Enemies
	void checkBulletHit(sf::FloatRect bulletBounds, float BposX, float BposY);
	void checkPlayerRange();
	void updateEnemiesAnimation();
	void updateEnemiesPos(sf::Vector2i dir);
	void updateEenmiesAtk();
	void updateEnemies(sf::Vector2i dir);
	

	//render Enemies
	void renderEnemies(sf::RenderWindow& target);
};

