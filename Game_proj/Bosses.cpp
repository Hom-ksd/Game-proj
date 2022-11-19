#include "Bosses.h"

void Bosses::initVariable()
{
	this->health = this->maxHealth;
	this->enemyRect = sf::IntRect(0, 0, 64, 64);
	this->isDead = false;
	this->isTurnLeft = false;
	this->isWalk = false;
	this->walkSpeed = 5.5f;
	this->normalizeSpeed = this->walkSpeed / 2 + sqrt(this->walkSpeed / 2);
	this->moveEnemy.x = 0.f;
	this->moveEnemy.y = 0.f;
	this->isInPlayerRange = false;
	this->playerRange = 75.f;
	this->isAtk = false;
	this->checkisdead = false;

	this->heigth = 64;
	this->width = 64;
	this->index_atk = { 0, 128 };
	this->index_die = { 0, 256 };
	this->index_dmg = { 0, 192 };
	this->index_idle = { 0, 0 };
	this->index_walk = { 0, 64 };

	this->atkState = false;

	this->score = 300.f;
	//std::cout << " " << this->index_walk.x;
}

void Bosses::initEnemySprite()
{
	this->enemySprite.setTexture(this->enemyTexture);
	this->enemySprite.setPosition(this->spawn_x, this->spawn_y);
	this->enemySprite.setTextureRect(this->enemyRect);
	this->enemySprite.setScale(3.f, 3.f);
}

Bosses::Bosses(sf::Texture* texture, float pos_x, float pos_y, float HP, float DMG)
{
	this->enemyTexture = *texture;
	this->spawn_x = pos_x;
	this->spawn_y = pos_y;
	this->maxHealth = HP;
	this->enemyDmg = DMG;
	this->initVariable();
	this->initEnemySprite();
}


const sf::Vector2f Bosses::getEnemyPos() const
{
	return this->enemySprite.getPosition();
}

const float Bosses::getEnemyHealth() const
{
	return this->health;
}

const float Bosses::getEnemyMaxHealth() const
{
	return this->maxHealth;
}

const bool Bosses::getEnemyState() const
{
	return this->isDead;
}

const sf::FloatRect Bosses::getBounds() const
{
	return sf::FloatRect(sf::Vector2f(this->enemySprite.getGlobalBounds().left + this->width / 2, this->enemySprite.getGlobalBounds().top + this->heigth * 1.5), sf::Vector2f(this->width, this->heigth));
}

void Bosses::damageEnemy(float amount)
{
	this->health -= amount;
	if (this->health <= 0) {
		//std::cout << "enemy die!\n";
		this->checkisdead = true;
		this->isDead = true;
	}
}

const bool Bosses::getEnemyAtk() const
{
	return this->atkState;
}

void Bosses::checkBulletHit(sf::FloatRect bulletBounds, float BposX, float BposY)
{
	float enemy_top = this->enemySprite.getPosition().x;
	float enemy_bot = enemy_top + this->enemySprite.getGlobalBounds().height;
	float enemy_left = this->enemySprite.getPosition().y;
	float enemy_right = enemy_left + this->enemySprite.getGlobalBounds().width;
}

void Bosses::checkPlayerRange()
{
	float x = this->playerPos.x;
	float y = this->playerPos.y;
	float r = sqrt(x * x + y * y);
	if (r <= this->playerRange) {
		this->isInPlayerRange = true;
		this->isWalk = false;
		this->atkState = true;
	}
	else {
		this->isInPlayerRange = false;
		this->isWalk = true;
		this->atkState = false;
	}
}

void Bosses::updateEnemiesAnimation()
{
	this->time = this->clock.getElapsedTime();
	if (this->time.asMilliseconds() > 100) {
		if (!this->isDead) {
			if (this->isInPlayerRange == true) {
				this->updateEenmiesAtk();
			}
			else if (this->isWalk == true) {
				if (this->isTurnLeft == false) {
					this->enemyRect = sf::IntRect(this->index_walk.x, this->index_walk.y, this->width, this->heigth);
				}
				else if (this->isTurnLeft == true) {
					this->enemyRect = sf::IntRect(this->index_walk.x + this->width, this->index_walk.y, -this->width, this->heigth);
				}
				this->index_walk.x += 64;
				if (this->index_walk.x > 448) {
					this->index_walk.x = 0;
				}
			}
		}
		this->enemySprite.setTextureRect(this->enemyRect);
		this->clock.restart();
	}
}

void Bosses::updateEnemiesPos(sf::Vector2i dir)
{
	double r = this->playerPos.y / this->playerPos.x;
	double dir_player = atan(r);;
	dir_player *= 180 / 3.14;
	float dir_x = this->walkSpeed * abs(cos(dir_player));
	float dir_y = this->walkSpeed * abs(sin(dir_player));
	if (this->playerPos.x < 0 && this->playerPos.y == 0) {
		dir_x = 0 - dir_x;

		this->isTurnLeft = true;
	}
	else if (this->playerPos.x > 0 && this->playerPos.y > 0) { // RU
		dir_y = 0 - dir_y;

		this->isTurnLeft = false;
	}
	else if (this->playerPos.x > 0 && this->playerPos.y < 0) { // RD
		dir_player += 360;

		this->isTurnLeft = false;
	}
	else if (this->playerPos.x < 0 && this->playerPos.y > 0) { // LU
		dir_player = 180 + dir_player;
		dir_y = 0 - dir_y;
		dir_x = 0 - dir_x;

		this->isTurnLeft = true;
	}
	else if (this->playerPos.x < 0 && this->playerPos.y < 0) { // LD
		dir_player += 180;
		dir_x = 0 - dir_x;

		this->isTurnLeft = true;
	}

	this->isWalk = true;
	this->enemySprite.move(dir_x, dir_y);

	float x = this->enemySprite.getPosition().x;
	float y = this->enemySprite.getPosition().y;
	if (x <= 72.f && y <= 125.f) {
		this->enemySprite.setPosition(72.f, 125.f);
	}
	else if (x <= 72.f) {
		this->enemySprite.setPosition(72.f, y);
	}
	else if (y <= 125.f) {
		this->enemySprite.setPosition(x, 125.f);
	}

	if (x >= 7860.f && y <= 125.f) {
		this->enemySprite.setPosition(7860.f, 125.f);
	}
	else if (x <= 72.f && y >= 7920.f) {
		this->enemySprite.setPosition(72.f, 7920.f);
	}
	else if (x >= 7860.f && y >= 7920.f) {
		this->enemySprite.setPosition(7860.f, 7920.f);
	}
	else if (x >= 7860.f) {
		this->enemySprite.setPosition(7860.f, y);
	}
	else if (y >= 7920.f) {
		this->enemySprite.setPosition(x, 7920.f);
	}
	//std::cout << dir_x << " " << dir_y << "\n";
}

void Bosses::updateEenmiesAtk()
{
	this->time = this->clock.getElapsedTime();
	this->atkTime = this->atkClock.getElapsedTime();
	if (this->atkTime.asMilliseconds() > 2000) {
		this->isAtk = true;
		this->atkClock.restart();
	}
	if (this->time.asMilliseconds() > 50) {
		if (this->isAtk) {
			if (this->isTurnLeft) {
				this->enemyRect = sf::IntRect(this->index_atk.x + this->width, this->index_atk.y, -this->width, this->heigth);
			}
			else {
				this->enemyRect = sf::IntRect(this->index_atk.x, this->index_atk.y, this->width, this->heigth);
			}
			this->index_atk.x += 64;
			if (this->index_atk.x > 256) {
				this->index_atk.x = 0;
				this->isAtk = false;
			}
		}
		else {
			if (this->isTurnLeft) {
				this->enemyRect = sf::IntRect(this->index_idle.x + this->width, this->index_idle.y, -this->width, this->heigth);
			}
			else {
				this->enemyRect = sf::IntRect(this->index_idle.x, this->index_idle.y, this->width, this->heigth);
			}
			this->index_idle.x += 64;
			if (this->index_idle.x > 448) {
				this->index_idle.x = 0;
			}
		}
		this->enemySprite.setTextureRect(this->enemyRect);
		this->clock.restart();
	}
}

void Bosses::updateEnemies(sf::Vector2i dir)
{
	this->originPoint = this->enemySprite.getPosition();
	this->playerPos.x = dir.x - this->originPoint.x - 26.f;
	this->playerPos.y = dir.y - this->originPoint.y - 26.f;
	this->playerPos.y = 0 - this->playerPos.y;

	this->checkPlayerRange();

	if (this->isInPlayerRange == false)
	{
		this->index_atk.x = 0;
		this->updateEnemiesPos(dir);
	}

	if (this->checkisdead == false) this->updateEnemiesAnimation();
}

void Bosses::renderEnemies(sf::RenderWindow& target)
{
	target.draw(this->enemySprite);
}
