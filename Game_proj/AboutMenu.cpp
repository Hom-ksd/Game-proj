#include "AboutMenu.h"

AboutMenu::AboutMenu(float width, float height)
{
	if (!this->font.loadFromFile("Fonts/ConnectionIii-Rj3W.otf")) {

	}
	this->selectedItem = 2;
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setFont(this->font);
		this->menu[i].setFillColor(sf::Color::White);
		this->menu[i].setPosition(sf::Vector2f(width / 2, height / (maxItem + 1) * (i + 1)));
		this->menu[i].setCharacterSize(32);
		if (i == 0) {
			this->menu[i].setString("65010049");
			this->menu[i].setCharacterSize(80);
		}
		if (i == 1) {
			this->menu[i].setString("Kasidej Putthwong");
			this->menu[i].setCharacterSize(80);
		}
		if (i == 2) {
			this->menu[i].setString("Back");
		}
		this->menu[i].setOrigin(this->menu[i].getLocalBounds().width / 2, this->menu[i].getLocalBounds().height / 2);
	}
	this->menu[this->selectedItem].setFillColor(sf::Color::Red);
}

AboutMenu::~AboutMenu()
{
}

void AboutMenu::MoveUp()
{
	if (this->selectedItem - 1 >= 1) {
		this->menu[this->selectedItem].setFillColor(sf::Color::White);
		this->selectedItem--;
		this->menu[this->selectedItem].setFillColor(sf::Color::Red);

	}
}

void AboutMenu::MoveDown()
{
	if (this->selectedItem + 1 < maxItem) {
		this->menu[this->selectedItem].setFillColor(sf::Color::White);
		this->selectedItem++;
		this->menu[this->selectedItem].setFillColor(sf::Color::Red);

	}
}

const int AboutMenu::getPressedItem() const
{
	return this->selectedItem;
}

void AboutMenu::setPos(float posx, float posy)
{
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setPosition(sf::Vector2f(this->menu[i].getPosition().x + posx, this->menu[i].getPosition().y + posy));
	}
}


void AboutMenu::renderMenu(sf::RenderWindow& window)
{
	for (int i = 0; i < maxItem; i++) {
		window.draw(this->menu[i]);
	}
}
