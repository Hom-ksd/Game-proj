#include "LeaderBoard.h"

void LeaderMenu::initFile()
{
	int cnt = 0;
	this->Leader.open("leader.txt");
	for (int i = 0; i < 5; i++) {
		std::string stemp;
		std::string itemp;
		this->Leader >> stemp;
		this->Leader >> itemp;
		this->data.push_back({ atoi(itemp.c_str()),stemp });
		std::string sdata = stemp + " " + itemp + "\n";
		//std::cout << sdata;
	}
	this->Leader.close();
}

LeaderMenu::LeaderMenu(float width, float height)
{
	if (!this->font.loadFromFile("Fonts/SuperLegendBoy-4w8Y.ttf")) {

	}
	this->initFile();
	this->selectedItem = 5;
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setFont(this->font);
		this->menu[i].setFillColor(sf::Color::White);
		this->menu[i].setPosition(sf::Vector2f(width / 6, height / (maxItem + 1) * (i + 1)));
		this->menu[i].setCharacterSize(40);
		if (i == maxItem - 1) {
			this->menu[i].setString("Main Menu");
			this->menu[i].setCharacterSize(32);
			this->menu[i].setPosition(sf::Vector2f(width / 2, height / (maxItem + 1) * (i + 1)));
			this->menu[i].setOrigin(this->menu[i].getLocalBounds().width / 2, this->menu[i].getLocalBounds().height / 2);
		}
		else {
			if (i < this->data.max_size()) this->menu[i].setString(this->data[i].second + " " + std::to_string(this->data[i].first));
			else this->menu[i].setString("");
		}
	}
	this->menu[this->selectedItem].setFillColor(sf::Color::Red);
}

void LeaderMenu::addData(std::string name, int score)
{
	this->Leader.open("leader.txt", std::fstream::app);
	int cnt = 0;
	for (auto i : data) {
		//std::cout << i.first << " " << i.second << "\n";
		cnt++;
	}
	this->data.push_back({ score,name});
	std::string temp = this->data[cnt].second + " " + std::to_string(this->data[cnt].first) + "\n";
	this->Leader << temp;
	this->Leader.close();
}

void LeaderMenu::updateData()
{
	std::sort(this->data.begin(), this->data.end());
	std::reverse(this->data.begin(), this->data.end());
	this->data.pop_back();
	this->Leader.open("leader.txt", std::ofstream::out | std::ofstream::trunc);
	int cnt = 0;
	for (auto i : this->data) {
		this->Leader << i.second << " " << std::to_string(i.first) << "\n";
		this->menu[cnt].setString(this->data[cnt].second + " " + std::to_string(this->data[cnt].first));
		cnt++;
	}
	this->Leader.close();
}

void LeaderMenu::updateString()
{
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setCharacterSize(50);
		if (i == maxItem - 1) {
			this->menu[i].setString("Main Menu");
			this->menu[i].setCharacterSize(32);
		}
		else {
			this->menu[i].setString(this->data[i].second + " " + std::to_string(this->data[i].first));
		}
		this->menu[i].setOrigin(this->menu[i].getLocalBounds().width / 2, this->menu[i].getLocalBounds().height / 2);
	}
}

const int LeaderMenu::getPressedItem() const
{
	return this->selectedItem;
}

void LeaderMenu::setPos(float posx, float posy)
{
	for (int i = 0; i < maxItem; i++) {
		this->menu[i].setPosition(sf::Vector2f(this->menu[i].getPosition().x + posx, this->menu[i].getPosition().y + posy));
	}
}


void LeaderMenu::renderMenu(sf::RenderWindow& window)
{
	for (int i = 0; i < maxItem; i++) {
		window.draw(this->menu[i]);
	}
}
