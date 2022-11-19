#include "Wands.h"

void Wands::initVariable()
{
	this->wandsLvl = 0;
	this->wandsExp = 0.f;
	for (int i = 0; i < 12; i++) {
		this->wandExpCapPerLvl[i] = 100.f + 150.f * ((i + 1.f) * 1.5f);
	}
	this->heigth = 56;
	this->width = 22;
	this->windowHeigth = 720; 
	this->windowWidth = 1280;
	this->playerHeigth = 36;
	this->playerWidth = 36;
	this->wandRect = sf::IntRect(0, 0, this->width, this->heigth);
}

void Wands::initWandTexture()
{
	this->wandTexture.loadFromFile("style_sheet/Wands/Wands-Green-x2.png");
}

void Wands::initWandSprite()
{
	this->wandSprite.setTexture(this->wandTexture);
	this->wandSprite.setScale(1.2f, 1.2f);
	this->wandSprite.setOrigin(sf::Vector2f(this->width / 2.f,this->heigth));
}

Wands::Wands()
{
	this->initVariable();
	this->initWandTexture();
	this->initWandSprite();
}

void Wands::addWandLvl(float amount)
{
	this->wandsExp += amount;
}

void Wands::updateWandLevel()
{
	if (this->wandsLvl < 12 && this->wandsExp > this->wandExpCapPerLvl[this->wandsLvl]) {
		this->wandsExp -= this->wandExpCapPerLvl[this->wandsLvl];
		this->wandsLvl += 1;
	}
}

void Wands::updateWandSprite()
{	
	this->wandRect = sf::IntRect(this->width * this->wandsLvl, 0, this->width, this->heigth);
	this->wandSprite.setTextureRect(this->wandRect);
}

void Wands::updateMousePos(sf::RenderWindow& target)
{
	this->mousePosWindow = sf::Mouse::getPosition(target);
	this->mousePosView = target.mapPixelToCoords(this->mousePosWindow);
	//std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";
}

void Wands::updateWandTarget(int playerPosX, int playerPosY)
{
	double x = this->mousePosView.x - playerPosX;
	double y = 0 - (this->mousePosView.y - playerPosY);
	double r = y / x;
	this->rotation = atan(r);
	this->rotation *= 180 / 3.14;
	if (x < 0 && y < 0) {
		this->rotation = 270 - this->rotation;
	}
	else if (x < 0 && y > 0) {
		this->rotation = 360 - (90 + this->rotation);
	}
	else if (x > 0 && y < 0) {
		this->rotation = 180 - (90 + this->rotation);
;	}
	else if (x > 0 && y > 0) {
		this->rotation = 90 - this->rotation;
	}
	this->direction.x = x;
	this->direction.y = -y;
	//std::cout << rotation << " " << x << " " << y  << "\n";
	this->wandSprite.setRotation(this->rotation);
}

void Wands::updateWandPos(int playerPosX, int playerPosY)
{
	this->wandSprite.setPosition(playerPosX,playerPosY);
}

void Wands::updateWand(sf::RenderWindow& target, sf::Vector2i playerPos)
{
	this->updateWandSprite();
	this->updateWandLevel();
	this->updateWandTarget(playerPos.x + this->playerWidth, playerPos.y + this->playerHeigth);
	this->updateWandPos(playerPos.x + this->playerWidth,playerPos.y + this->playerHeigth);
	this->updateMousePos(target);
}

float Wands::returnWandTarget()
{
	return this->rotation;
}

sf::Vector2f Wands::returnWandDirection()
{	
	return sf::Vector2f(this->direction * 0.1f);
}

const int Wands::getWandLvl() const
{
	return this->wandsLvl;
}

const float Wands::getMaxWandExp() const
{
	return this->wandExpCapPerLvl[this->wandsLvl];
}

const float Wands::getWandExp() const
{
	return this->wandsExp;
}

void Wands::renderWand(sf::RenderWindow& target)
{
	target.draw(this->wandSprite);
}