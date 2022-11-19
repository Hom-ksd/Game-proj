#include "InputnameMenu.h"

void InputnameMenu::initfont()
{
	this->font.loadFromFile("Fonts/SuperLegendBoy-4w8Y.ttf");
}

void InputnameMenu::inputLogic(int charType)
{
	if (charType != DELETE_KEY && charType != ESCAPE_KEY && charType != ENTER_KEY) {
		if (this->text.str().length() < this->limit) this->text << static_cast<char>(charType);
	}
	else if (charType == DELETE_KEY) {
		if (text.str().length() > 0) {
			this->delLastChar();
		}
	}
	else if (charType == ENTER_KEY) {
		this->isEnter = true;
	}
	this->textbox.setString(this->text.str() + "_");
}

void InputnameMenu::delLastChar()
{
	std::string t = this->text.str();
	std::string newT = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newT += t[i];
	}
	this->text.str("");
	this->text << newT;

	this->textbox.setString(this->text.str());
}

InputnameMenu::InputnameMenu(float width, float height)
{
	this->initfont();
	this->limit = 15;
	this->name.setCharacterSize(40);
	this->name.setFillColor(sf::Color::White);
	this->name.setString("Enter Your name");
	this->name.setPosition(sf::Vector2f(width / 6, height / 3));

	this->textbox.setCharacterSize(40);
	this->textbox.setFillColor(sf::Color::White);
	this->textbox.setString("_");
	this->textbox.setPosition(sf::Vector2f(width / 6, height / 3 * 2));
}

void InputnameMenu::typedOn(sf::Event input)
{
	int charType = input.text.unicode;
	if (charType < 128) {
		this->inputLogic(charType);
	}
}

void InputnameMenu::setPos(float posx, float posy)
{
	this->name.setPosition(sf::Vector2f(this->name.getPosition().x + posx, this->name.getPosition().y + posy));
	this->textbox.setPosition(sf::Vector2f(this->textbox.getPosition().x + posx, this->textbox.getPosition().y + posy));
}

const sf::Vector2f InputnameMenu::getPos() const
{
	return this->name.getPosition();
}

const bool InputnameMenu::getEnter() const
{
	return this->isEnter;
}

const std::string InputnameMenu::getName() const
{
	return this->text.str();
}


void InputnameMenu::resetEnter()
{
	this->isEnter = false;
}

void InputnameMenu::renderTextBox(sf::RenderWindow& target)
{
	target.draw(this->name);
	//target.draw(this->textbox);
}
