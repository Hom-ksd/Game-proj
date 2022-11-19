#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Wands.h"

class Player
{
private:
	//Variable
	sf::Texture playerTexture;
	sf::Sprite playerSprite; 
	//image per frame = 24 x 24 pixels
	//idle 4 frame
	//walking 7 frame

	//delay animation player
	sf::Clock clock;
	sf::Time time;

	//player frame
	int heigth;
	int width;
	int xpos_idle;
	int xpos_walk;
	bool isWalk;
	bool isTurnLeft;
	float movementSpeed;
	float normalizeSpeed;
	sf::IntRect playerRect;


	//moving player
	struct movePlayer {
		float x;
		float y;
	}movePlayer;
	
	//Health
	float health;
	float maxHealth;

	//Player logic
	bool isDead;

	//Private function
	void initVariable();
	void initPlayerTexture();
	void initPlayerSprite();

public:
	Player();
	
	//invis player
	sf::Clock invisClock;
	sf::Time invisTime;
	float invis;
	bool invisState;

	//update player
	void updatePlayerStatus(sf::Event ev);
	void updatePlayerAnimation();
	void updatePlayer(sf::Event ev);
	void stopPlayermove();
	void stopPlayermoveX();
	void stopPlayermoveY();

	sf::Vector2i returnPlayerPos();
	sf::Vector2i returnPlayerCenter();

	const float& getPlayerHealth() const;
	const float& getPlayerMaxHealth() const;
	const sf::FloatRect getGlobalBounds() const;

	void resetState();
	void damagedPlayer(float amount);
	void HealedPlayer(float amount);
	const bool getPlayerState() const;

	//render player
	void renderPlayer(sf::RenderWindow &target);
};

