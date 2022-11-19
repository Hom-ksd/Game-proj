#include "Player.h"

void Player::initVariable()
{
	this->heigth = 24;
	this->width = 24;
	this->xpos_idle = 0;
	this->xpos_walk = 96;
	this->isWalk = false;
	this->isTurnLeft = false;
	this->movementSpeed = 6.f;
	this->playerRect = sf::IntRect{ 0,0,this->width,this->heigth };
	this->movePlayer.x = 0;
	this->movePlayer.y = 0;
	this->normalizeSpeed = (6.f * sin(atan(1)));
	//std::cout << this->normalizeSpeed;
	this->isDead = false;
	this->maxHealth = 1000.f;
	this->health = this->maxHealth;

	this->invis = 200.f;
	this->invisState = false;
}

void Player::initPlayerTexture()
{
	this->playerTexture.loadFromFile("style_sheet/Player_sheet/DinoSprites - tard.png");
}	

void Player::initPlayerSprite()
{
	this->playerSprite.setTexture(this->playerTexture);
	this->playerSprite.setScale(3.0f, 3.0f);
	this->playerSprite.setPosition(4000.f, 4000.f);
}

Player::Player()
{
	this->initVariable();
	this->initPlayerTexture();
	this->initPlayerSprite();
}

void Player::updatePlayerStatus(sf::Event ev)
{	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->movePlayer.x = this->movementSpeed;
		this->movePlayer.y = 0.f;
		this->isWalk = true;
		this->isTurnLeft = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->movePlayer.y = -this->normalizeSpeed;
			//this->movePlayer.x = this->normalizeSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->movePlayer.y = this->normalizeSpeed;
			//this->movePlayer.x = this->normalizeSpeed;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->movePlayer.x = -this->movementSpeed;
		this->movePlayer.y = 0.f;
		this->isWalk = true;
		this->isTurnLeft = true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			this->movePlayer.y = -this->normalizeSpeed;
			this->movePlayer.x = -this->normalizeSpeed;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			this->movePlayer.y = this->normalizeSpeed;
			this->movePlayer.x = -this->normalizeSpeed;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->movePlayer.y = -this->movementSpeed;
		this->movePlayer.x = 0.f;
		this->isWalk = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->movePlayer.y = this->movementSpeed;
		this->movePlayer.x = 0.f;
		this->isWalk = true;
	}
	else{
		this->movePlayer.x = 0.f;
		this->movePlayer.y = 0.f;
		this->isWalk = false;
	}

	float x = this->playerSprite.getPosition().x;
	float y = this->playerSprite.getPosition().y;
	if (x <= 72.f && y <= 125.f) {
		this->playerSprite.setPosition(72.f, 125.f);
	}
	else if (x <= 72.f) {
		this->playerSprite.setPosition(72.f, y);
	}
	else if (y <= 125.f) {
		this->playerSprite.setPosition(x, 125.f);
	}
	
	if (x >= 7860.f && y <= 125.f) {
		this->playerSprite.setPosition(7860.f, 125.f);
	}
	else if (x <= 72.f && y >= 7920.f) {
		this->playerSprite.setPosition(72.f, 7920.f);
	}
	else if (x >= 7860.f && y >= 7920.f) {
		this->playerSprite.setPosition(7860.f, 7920.f);
	}
	else if (x >= 7860.f) {
		this->playerSprite.setPosition(7860.f, y);
	}
	else if (y >= 7920.f) {
		this->playerSprite.setPosition(x, 7920.f);
	}

	this->playerSprite.move(this->movePlayer.x,this->movePlayer.y);
}

void Player::updatePlayerAnimation()
{
	this->time = this->clock.getElapsedTime();
	if (this->time.asMilliseconds() > 100) {
		if (this->isWalk == false) {
			if (this->isTurnLeft) {
				this->playerRect = sf::IntRect{ this->xpos_idle + this->width, 0,-this->width,this->heigth };
			}
			else {
				this->playerRect = sf::IntRect{ this->xpos_idle,0,this->width,this->heigth };
			}
			this->playerSprite.setTextureRect(this->playerRect);
			this->xpos_idle += 24;
			if (this->xpos_idle >= 96) {
				this->xpos_idle = 0;
			}
		}
		else {
			if (this->isTurnLeft) {
				this->playerRect = sf::IntRect{ this->xpos_walk + this->width, 0,-this->width,this->heigth };
			}
			else {
				this->playerRect = sf::IntRect{ this->xpos_walk,0,this->width,this->heigth };
			}
			this->xpos_walk += 24;
			if (this->xpos_walk >= 240) {
				this->xpos_walk = 96;
			}
		}
		this->playerSprite.setTextureRect(this->playerRect);
		this->clock.restart();
	}
}

void Player::updatePlayer(sf::Event ev)
{
	this->updatePlayerStatus(ev);
	this->updatePlayerAnimation();
}

void Player::stopPlayermove()
{
	this->movePlayer.x = 0;
	this->movePlayer.y = 0;
}

void Player::stopPlayermoveX()
{
	this->movePlayer.x = 0;
}

void Player::stopPlayermoveY()
{
	this->movePlayer.y = 0;
}

sf::Vector2i Player::returnPlayerPos()
{
	int x = this->playerSprite.getPosition().x;
	int y = this->playerSprite.getPosition().y;
	return sf::Vector2i(x,y);
}

sf::Vector2i Player::returnPlayerCenter()
{
	return sf::Vector2i(this->width ,this->heigth );
}


const float& Player::getPlayerHealth() const
{
	return this->health;
}

const float& Player::getPlayerMaxHealth() const
{
	return this->maxHealth;
}

const sf::FloatRect Player::getGlobalBounds() const
{
	return this->playerSprite.getGlobalBounds();
}

void Player::resetState()
{
	this->isDead = false;
}

void Player::damagedPlayer(float amount)
{
	this->health -= amount;
	if (this->health <= 0.f) {
		this->isDead = true;
	}
}

void Player::HealedPlayer(float amount)
{
	this->health += amount;
	if (this->health > this->maxHealth) {
		this->health = this->maxHealth;
	}
}

const bool Player::getPlayerState() const
{
	return this->isDead;
}


void Player::renderPlayer(sf::RenderWindow& target)
{
	target.draw(this->playerSprite);
}