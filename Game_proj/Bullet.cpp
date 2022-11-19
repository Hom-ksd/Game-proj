#include "Bullet.h"

void Bullet::initVariable()
{
	this->heigth = 24;
	this->width = 48;
	this->bulletRect = sf::IntRect(0, 0, this->width, this->heigth);
	this->animateCnt = 0;
	this->bulletSpeed = 15.f;
}
/*
void Bullet::initBulletTexture()
{
	this->bulletTexture.loadFromFile("style_sheet/Fire_Effect/Green.png");
}
*/
void Bullet::initBulletSprite()
{
	this->bulletSprite.setTexture(this->bulletTexture);
	this->bulletSprite.setOrigin(sf::Vector2f(this->width, this->heigth / 2.f));
	this->bulletSprite.setScale(1.f, 1.f);
}

void Bullet::iniitbulletDir()
{
	float x = this->direction.x;
	float y = this->direction.y;
	float at = atan(y / x);
	float tempx = 1.0f * cos(at);
	float tempy = 1.0f * sin(at);
	if (x < 0) {
		tempx = 0 - tempx;
		tempy = 0 - tempy;
	}
	//std::cout << at << " x : " << tempx << " y : " << tempy << " " << r << "\n";
	this->direction = { tempx , tempy };
}

Bullet::Bullet(sf::Texture* texture, float pos_x, float pos_y, float dir_x, float dir_y,float rotation)
{
	this->initVariable();
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->bulletTexture = *texture;
	this->initBulletSprite();

	float wandSize = 56.f;
	float at = rotation * 3.14 / 180;
	float tempx = wandSize * sin(at) + 5.f;
	float tempy = wandSize * cos(at) + 5.f;

	//std::cout << pos_x << " " << pos_y << " " << tempx << " " << tempy << "\n";

	this->bulletSprite.setPosition(pos_x + tempx, pos_y - tempy);
	this->bulletRotation = rotation;
	this->bulletSprite.setRotation(this->bulletRotation - 90.f);
	this->iniitbulletDir();
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->bulletSprite.getGlobalBounds();
}

const sf::Vector2f Bullet::getPos() const
{
	return this->bulletSprite.getPosition();
}

void Bullet::setScale(float x, float y)
{
	this->bulletSprite.setScale(x, y);
}

void Bullet::updateBulletAnimation()
{
	this->time = this->clock.getElapsedTime();
	if(this->time.asMicroseconds() > 100)
	{
		this->bulletRect = sf::IntRect(this->animateCnt * this->width, 0, this->width, this->heigth);
		this->animateCnt += 1;
		if (animateCnt >= 30) {
			animateCnt = 0;
		}
		this->bulletSprite.setTextureRect(this->bulletRect);
		this->clock.restart();
	}
}


void Bullet::updateBulletPos()
{
	this->bulletSprite.move(this->bulletSpeed * this->direction);
}


void Bullet::updateBullet()
{
	this->updateBulletAnimation();
	this->updateBulletPos();
}

void Bullet::renderBullet(sf::RenderWindow& target)
{
	target.draw(this->bulletSprite);
}