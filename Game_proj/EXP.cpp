#include "EXP.h"

void EXP::initVariable()
{
	this->playerRange = 50.f;
}

void EXP::initSprite()
{
	this->expSprite.setTexture(this->expTexture);
	this->expSprite.setPosition(this->position);
	this->expSprite.setScale(2.f, 2.f);
}

EXP::EXP(sf::Vector2f spawn_pos,int type,float amount)
{
	this->type = type;
	this->position = spawn_pos;
	this->expTexture.loadFromFile("style_sheet/EXP.png");
	this->amount = amount;

	this->initVariable();
	this->initSprite();
}

const float EXP::getAmount() const
{
	return this->amount;
}

const sf::FloatRect EXP::getGlobalBound() const
{
	return this->expSprite.getGlobalBounds();
}

void EXP::setAmount(float amount)
{
	this->amount = amount;
}


void EXP::updateExp()
{

}

void EXP::renderExp(sf::RenderWindow& target)
{
	target.draw(this->expSprite);
}
