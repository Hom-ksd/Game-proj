#include "Foods.h"

void Foods::initVariable()
{
	this->healAmount = (rand() % 70) + 30;
}

void Foods::initSprite()
{
	this->foodSprite.setTexture(this->foodTexture);
	this->foodSprite.setPosition(this->spawn_pos);
	this->foodSprite.setScale(2.2f, 2.2f);
}

Foods::Foods(sf::Vector2f spawn_pos)
{
	srand(time(NULL));
	this->spawn_pos = spawn_pos;
	this->ss << "style_sheet/Food/" << rand() % 42 + 1 << ".png";
	//std::cout << ss.str() << "\n";
	this->foodTexture.loadFromFile(this->ss.str());
	this->initVariable();
	this->initSprite();
}

const sf::FloatRect Foods::getGlobalBounds() const
{
	return this->foodSprite.getGlobalBounds();
}

const float Foods::getHealAmount() const
{
	return this->healAmount;
}

void Foods::updateFood()
{
}

void Foods::renderFood(sf::RenderWindow& target)
{
	target.draw(this->foodSprite);
}
