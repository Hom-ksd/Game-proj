#include "Tile.h"
#include <SFML/Graphics/RenderTarget.hpp>

void Tile::initVariable()
{
	this->heigth = 16;
	this->width = 16;
}



Tile::Tile(float pos_x, float pos_y, float gridSizeF, sf::Texture& texture, sf::IntRect textureRect)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setPosition(pos_x, pos_y);
	this->texture = &texture;
	this->shape.setTexture(this->texture);
	this->shape.setTextureRect(textureRect);
}

void Tile::renderTile(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

const sf::Vector2f Tile::getTilePos() const
{
	return sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y);
}
