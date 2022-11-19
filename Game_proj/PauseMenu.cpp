#include "PauseMenu.h"

PauseMenu::PauseMenu(float width, float height)
{
	if (!this->font.loadFromFile("Fonts/ConnectionIii-Rj3W.otf")) {

	}
	this->selectedItem = 1;
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setFont(this->font);
		this->menu[i].setFillColor(sf::Color::White);
		this->menu[i].setPosition(sf::Vector2f(width / 2, height / (maxItem + 1) * (i + 1)));
		this->menu[i].setCharacterSize(32);
		if (i == 0) {
			this->menu[i].setString("PAUSE GAME");
			this->menu[i].setFillColor(sf::Color::Black);
			this->menu[i].setCharacterSize(80);
		}
		if (i == 1) {
			this->menu[i].setString("Resume");
		}
		if (i == 2) {
			this->menu[i].setString("Quit");
		}
		this->menu[i].setOrigin(this->menu[i].getLocalBounds().width / 2, this->menu[i].getLocalBounds().height / 2);
	}
	this->menu[this->selectedItem].setFillColor(sf::Color::Red);
}

void PauseMenu::MoveUp()
{
	if (this->selectedItem - 1 >= 1) {
		this->menu[this->selectedItem].setFillColor(sf::Color::White);
		this->selectedItem--;
		this->menu[this->selectedItem].setFillColor(sf::Color::Red);

	}
}

void PauseMenu::MoveDown()
{
	if (this->selectedItem + 1 < maxItem) {
		this->menu[this->selectedItem].setFillColor(sf::Color::White);
		this->selectedItem++;
		this->menu[this->selectedItem].setFillColor(sf::Color::Red);

	}
}

const int PauseMenu::getPressedItem() const
{
	return this->selectedItem;
}

const sf::Vector2f PauseMenu::getPos() const
{
	return this->menu[0].getPosition();
}

void PauseMenu::setPos(float posx, float posy)
{
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setPosition(sf::Vector2f(this->menu[i].getPosition().x + posx, this->menu[i].getPosition().y + posy));
	}
}


void PauseMenu::renderMenu(sf::RenderWindow& window)
{
	for (int i = 0; i < maxItem; i++) {
		window.draw(this->menu[i]);
	}
}
