#include "gameEngine.h"

void gameEngine::initVariables()
{
	this->fireRate = 250;
	this->endgame = false;
	this->isRenderTile = false;
	this->spawnRate = 500;
	this->cntSpawn = 0;
	this->maxSpawn = 30;
	this->kill_counter = 0;
	this->foodDropRate = 10;
	this->score = 0.f;
	this->isBossSpawn = false;
}

void gameEngine::initWindow()
{
	this->videomode.height = 720;
	this->videomode.width = 1280;

	this->window = new sf::RenderWindow(this->videomode, "Dinosaur of wizardry");

	this->window->setFramerateLimit(60);
}

void gameEngine::initView()
{
	this->view.setSize(this->window->getSize().x , this->window->getSize().y);
}

void gameEngine::initObject()
{
	this->player = new Player;
	this->wand = new Wands;

	this->Dmenu = new DeadMenu(this->window->getSize().x, this->window->getSize().y);

	this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);

	this->Pmenu = new PauseMenu(this->window->getSize().x, this->window->getSize().y);

	this->Amenu = new AboutMenu(this->window->getSize().x, this->window->getSize().y);

	this->Lmenu = new LeaderMenu(this->window->getSize().x, this->window->getSize().y);

	this->Emenu = new InputnameMenu(this->window->getSize().x, this->window->getSize().y);

	this->textures["Bullet"] = new sf::Texture();
	this->textures["Bullet"]->loadFromFile("style_sheet/Fire_Effect/Green.png");

	this->enemies_texture["Enemy"] = new sf::Texture();
	this->enemies_texture["Enemy"]->loadFromFile("style_sheet/Monster_sheet/LeshyLeafSpriteSheet.png");

	this->enemies_texture["Enemy2"] = new sf::Texture();
	this->enemies_texture["Enemy2"]->loadFromFile("style_sheet/Monster_sheet/Twig Blight Sprite Sheet.png");

	this->enemies_texture["Boss"] = new sf::Texture();
	this->enemies_texture["Boss"]->loadFromFile("style_sheet/Monster_sheet/Shardsoul Slayer Sprite Sheet.png");

	this->name.setString("Enter Your name");
	this->name.setFont(this->font);
	this->name.setCharacterSize(100);
	this->name.setOrigin(sf::Vector2f(this->name.getLocalBounds().width / 2, this->name.getLocalBounds().height / 2));
	this->name.setPosition(sf::Vector2f(this->view.getCenter().x, this->view.getCenter().y));

	this->Ename.setFont(this->font);
	this->Ename.setCharacterSize(60);
	//this->Ename.setOrigin(sf::Vector2f(this->Ename.getLocalBounds().width / 2, this->Ename.getLocalBounds().height / 2));
	this->Ename.setPosition(sf::Vector2f(this->view.getCenter().x, this->view.getCenter().y));

}

void gameEngine::initGUI()
{
	this->GUITexture = new sf::Texture();
	this->GuITexture2 = new sf::Texture();

	this->HPRect = sf::IntRect(72, 22, 49, 3);
	this->BHPRect = sf::IntRect(135, 20, 52, 7);

	this->GUITexture->loadFromFile("style_sheet/GUI/GUI.png");
	this->GuITexture2->loadFromFile("style_sheet/GUI/GUI2.png");
	
	this->HP.setSize(sf::Vector2f(288.f,16.f));
	this->HP.setTexture(this->GUITexture);
	this->HP.setTextureRect(this->HPRect);
	this->HP.setPosition(sf::Vector2f(6.f, 8.f));
	this->HP.setFillColor(sf::Color(255,0,0,200));
	
	this->BHP.setSize(sf::Vector2f(304.f,32.f));
	this->BHP.setTexture(this->GUITexture);
	this->BHP.setTextureRect(this->BHPRect);
	this->BHP.setPosition(sf::Vector2f(0.f, 0.f));

	this->exp.setSize(sf::Vector2f(288.f, 16.f));
	this->exp.setTexture(this->GuITexture2);
	this->exp.setTextureRect(this->HPRect);
	this->exp.setPosition(sf::Vector2f(6.f, 8.f));
	this->exp.setFillColor(sf::Color(255, 255, 255, 200));

	this->bexp.setSize(sf::Vector2f(304.f, 32.f));
	this->bexp.setTexture(this->GuITexture2);
	this->bexp.setTextureRect(this->BHPRect);
	this->bexp.setPosition(sf::Vector2f(0.f, 0.f));

	this->font.loadFromFile("Fonts/ConnectionIii-Rj3W.otf");
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(24);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(sf::Vector2f(0.f, 0.f));

	//this->player->damagedPlayer(20.f);

}

void gameEngine::initMenu()
{
	this->inMenu = true;
	this->play = false;
	this->leaderBoard = false;
	this->About = false;
	this->inDeadMenu = false;
	this->isPause = false;
	this->entername = false;
	this->keypressed = -1;
	this->Dkeypressed = -1;
	this->Pkeypressed = -1;
	this->checkPause = false;

	this->DeadMenuBG.setSize(sf::Vector2f(10000.f, 10000.f));
	this->DeadMenuBG.setFillColor(sf::Color(255, 255, 255, 125));
	this->DeadMenuBG.setPosition(sf::Vector2f(-1000.f, -1000.f));

	this->PauseMenuBG.setSize(sf::Vector2f(10000.f, 10000.f));
	this->PauseMenuBG.setFillColor(sf::Color(0, 0, 0, 125));
	this->PauseMenuBG.setPosition(sf::Vector2f(-1000.f, -1000.f));

	this->MenuBG.setSize(sf::Vector2f(this->view.getSize().x + 50.f,this->view.getSize().y));
	sf::Texture *menuTexture = new sf::Texture();
	menuTexture->loadFromFile("style_sheet/nature-animals-dinosaurs-prehistoric-wallpaper-preview.jpg");
	this->MenuBG.setTexture(menuTexture);
}

void gameEngine::initSound()
{
	this->buffer.loadFromFile("SoundTrack/Laser.wav");
	this->Sound.setBuffer(this->buffer);
	this->Sound.setVolume(20.f);

	this->BGbuffer.loadFromFile("SoundTrack/dungeon_theme_1.wav");
	this->BGSound.setBuffer(this->BGbuffer);
	this->BGSound.setLoop(true);
	this->BGSound.play();

	this->Overbuffer.loadFromFile("SoundTrack/Game_Over_3.wav");
	this->OverSound.setBuffer(this->Overbuffer);
}

void gameEngine::restart()
{
	this->player->resetState();
	this->initVariables();
	this->initObject();
	this->initGUI();
	for (auto* exp : this->exps) {
		this->exps.erase(this->exps.begin());
	}
	for (auto* food : this->foods) {
		this->foods.erase(this->foods.begin());
	}

	unsigned enemies_counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->damageEnemy(9999999.f);
		//del enemy if isDead == true;
		if (enemy->getEnemyState() == true) {
			this->enemies.erase(this->enemies.begin() + enemies_counter);
			enemies_counter--;
		}
		enemies_counter++;
	}

	unsigned enemies_counter2 = 0;
	for (auto* enemy : this->enemies2) {
		enemy->damageEnemy(9999999.f);
		//del enemy if isDead == true;
		if (enemy->getEnemyState() == true) {
			this->enemies2.erase(this->enemies2.begin() + enemies_counter2);
			enemies_counter2--;
		}
		enemies_counter2++;
	}

	unsigned enemies_counter3 = 0;
	for (auto* boss : this->boss) {
		boss->damageEnemy(9999999.f);
		//del enemy if isDead == true;
		if (boss->getEnemyState() == true) {
			this->boss.erase(this->boss.begin() + enemies_counter3);
			enemies_counter3--;
		}
		enemies_counter3++;
	}
}

gameEngine::gameEngine()
{
	this->initVariables();
	this->initWindow();
	this->initView();
	this->initObject();
	this->initGUI();
	this->initSound();
	this->initMenu();

}

gameEngine::~gameEngine()
{
	delete this->window;
	delete this->player;
	delete this->wand;

	for (auto& i : this->textures) {
		delete i.second;
	}
	
	for (auto& i : this->bullets) {
		delete i;
	}

	for (auto& i : this->enemies) {
		delete i;
	}

	for (auto& i : this->exps) {
		delete i;
	}

	for (auto& i : this->boss) {
		delete i;
	}

}

const bool gameEngine::running() const
{
	return this->window->isOpen();	
}

const bool gameEngine::getEndgame() const
{
	return this->endgame;
}

void gameEngine::pollEvent()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape && !this->inMenu && !this->isDead && !this->About && !this->leaderBoard) {
				this->isPause = true;
				this->play = false;
				this->Pkeypressed = -1;
				if(this->checkPause == false) {
					this->checkPause = true;
					this->MenuBG.setPosition(sf::Vector2f(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2));
					this->menu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
					this->Pmenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
					this->Lmenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
					this->Emenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
				}
					//std::cout << this->player->returnPlayerPos().x - this->view.getSize().x / 2 << " " << this->player->returnPlayerPos().y - this->view.getSize().y / 2 << "\n";
			}
			else if (this->ev.key.code == sf::Keyboard::W && this->isPause) {
				this->Pmenu->MoveUp();
			}
			else if (this->ev.key.code == sf::Keyboard::S && this->isPause) {
				this->Pmenu->MoveDown();
			}
			else if (this->ev.key.code == sf::Keyboard::Enter && this->isPause) {
				this->Pkeypressed = this->Pmenu->getPressedItem();
			}
			if (this->ev.key.code == sf::Keyboard::Enter && this->inMenu) {
				this->keypressed = this->menu->getPressedItem();
			}
			else if (this->ev.key.code == sf::Keyboard::W && this->inMenu) {
				this->menu->MoveUp();
			}
			else if (this->ev.key.code == sf::Keyboard::S && this->inMenu) {
				this->menu->MoveDown();
			}
			if (this->ev.key.code == sf::Keyboard::Enter && this->inDeadMenu) {
				this->Dkeypressed = this->Dmenu->getPressedItem();
			}
			else if (this->ev.key.code == sf::Keyboard::W && this->inDeadMenu) {
				this->Dmenu->MoveUp();
			}
			else if (this->ev.key.code == sf::Keyboard::S && this->inDeadMenu) {
				this->Dmenu->MoveDown();
			}
			if (this->ev.key.code == sf::Keyboard::Enter && this->About) {
				this->Akeypressed = this->Amenu->getPressedItem();
			}
			if (this->ev.key.code == sf::Keyboard::Enter && this->leaderBoard) {
				this->Lkeypressed = this->Lmenu->getPressedItem();
			}
			break;
		case sf::Event::TextEntered:
			if (this->entername) {
				this->Emenu->typedOn(this->ev);
			}
			break;
		}
	}
}

void gameEngine::SpawnEnemies()
{
	srand(time(NULL));
	int rnum = rand() % 12;
	while (!((this->spawnPoint[rnum].first > 72.f && this->spawnPoint[rnum].second > 125.f) && (this->spawnPoint[rnum].first < 7860.f && this->spawnPoint[rnum].second < 7920.f))) {
		rnum = rand() % 12;
	}
	int etype = rand() % 2;
	this->enemyTime = this->enemyClock.getElapsedTime();
	if (this->enemyTime.asMilliseconds() > this->spawnRate && this->cntSpawn < this->maxSpawn && !this->isBossSpawn) {
		float pos_x = this->player->returnPlayerPos().x;
		float pos_y = this->player->returnPlayerPos().y;
		if(etype == 0) {
			this->enemies.push_back(new Enemies(this->enemies_texture["Enemy"], this->spawnPoint[rnum].first, this->spawnPoint[rnum].second, (this->wand->getWandLvl() + 1) * 30, (this->wand->getWandLvl() + 1) * 40));
		}
		else if (etype == 1) {
			this->enemies2.push_back(new Enemies2(this->enemies_texture["Enemy2"], this->spawnPoint[rnum].first, this->spawnPoint[rnum].second, (this->wand->getWandLvl() + 1) * 50, (this->wand->getWandLvl() + 1) * 25));
		}
		this->enemyClock.restart();
		this->cntSpawn++;
		//std::cout << "spawn!\n";
	}
	if (this->enemyTime.asMilliseconds() > this->spawnRate && this->kill_counter >= 30 && !this->isBossSpawn) {
		this->boss.push_back(new Bosses(this->enemies_texture["Boss"],this->spawnPoint[rnum].first,this->spawnPoint[rnum].second,this->wand->getWandLvl() * 100.f + 300.f, this->wand->getWandLvl() * 50.f + 150.f));
		this->kill_counter -= 25;
		this->isBossSpawn = true;
	}
}

void gameEngine::updateDt()
{
	this->dt = this->dtClock.getElapsedTime().asSeconds();

}

void gameEngine::updateMenu()
{	
	//std::cout << this->isPause << " " << this->Pkeypressed << "\n";
	if (this->keypressed == 1) {
		this->restart();
		this->inMenu = false;
		this->play = true;
		this->keypressed = -1;
	}
	else if (this->keypressed == 2) {
		this->leaderBoard = true;
		this->inMenu = false;
		this->keypressed = -1;
	}
	else if (this->keypressed == 3) {
		this->About = true;
		this->inMenu = false;
		this->keypressed = -1;
	}
	else if (this->keypressed == 4) {
		this->endgame = true;
		this->inMenu = false;
		this->keypressed = -1;
	}
	//std::cout << this->Dkeypressed << "\n";
	if (this->Dkeypressed == 1) {
		this->restart();
		this->play = true;
		this->inDeadMenu = false;
		this->Dkeypressed = -1;
		this->keypressed = -1;
		this->checkPause = false;
	}
	else if (this->Dkeypressed == 2) {
		this->entername = true;
		this->inDeadMenu = false;
		this->checkPause = false;
		this->name.setPosition(sf::Vector2f(this->view.getCenter().x, this->view.getCenter().y - this->view.getSize().y / 3));
		this->Ename.setPosition(sf::Vector2f(this->view.getCenter().x - this->view.getSize().x / 3, this->view.getCenter().y));
		this->Dkeypressed = -1;
		this->keypressed = -1;
		this->BGSound.setVolume(100.f);
	}

	if (this->Pkeypressed == 1) {
		this->isPause = false;
		this->play = true;
		this->checkPause = false;
		this->Pmenu = new PauseMenu(this->window->getSize().x, this->window->getSize().y);
		this->Pkeypressed = -1;
		this->keypressed = -1;
	}
	else if (this->Pkeypressed == 2) {
		this->play = false;
		this->isPause = false;
		this->inMenu = true;
		this->checkPause = false;
		this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
		this->Amenu = new AboutMenu(this->window->getSize().x, this->window->getSize().y);
		this->Lmenu = new LeaderMenu(this->window->getSize().x, this->window->getSize().y);
		this->Emenu = new InputnameMenu(this->window->getSize().x, this->window->getSize().y);
		this->menu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
		this->Amenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
		this->Lmenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
		this->Emenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
		this->MenuBG.setPosition(sf::Vector2f(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2));
		this->Pkeypressed = -1;
		this->keypressed = -1;
	}

	if (this->Akeypressed == 2) {
		this->About = false;
		this->inMenu = true;
		this->Akeypressed = -1;
	}
	
	if (this->Lkeypressed == 5) {
		this->leaderBoard = false;
		this->inMenu = true;
		this->Lkeypressed = -1;
	}

	if (this->Emenu->getEnter() && this->entername) {
		std::cout << this->Emenu->getName() << "\n";
		std::string temp = "Unknow";
		if (!(this->Emenu->getName() == "")) {
			this->Lmenu->addData(this->Emenu->getName(), this->score);
		}
		else this->Lmenu->addData(temp, this->score);
		this->Lmenu->updateData();
		this->entername = false;
		this->leaderBoard = true;
		this->Emenu->resetEnter();
	}
}

void gameEngine::updateSound()
{

}

void gameEngine::updateCheckBulletAndEnemies()
{
	unsigned counter = 0;
	float spawnfood;
	for (auto& bullet : this->bullets) {
		bool check = false;
		for (auto& enemy : this->enemies) {
			enemy->timeDmg = enemy->delayDmg.getElapsedTime();
			//std::cout << bullet->getBounds().intersects(enemy->getBounds()) << "\n";
			if(bullet->getBounds().intersects(enemy->getBounds())) {
				enemy->damageEnemy(10.f * (this->wand->getWandLvl() + 1));
				check = true;
				if (enemy->getEnemyState()) {
					spawnfood = rand() % 100;
					if (spawnfood <= this->foodDropRate) {
						this->foods.push_back(new Foods(sf::Vector2f(enemy->getEnemyPos() + sf::Vector2f(enemy->getBounds().width / 2, enemy->getBounds().height / 2))));
						this->foodDropRate = 10;
					}
					else {
						this->foodDropRate += 5;
					}
					this->exps.push_back(new EXP(enemy->getEnemyPos() + sf::Vector2f(enemy->getBounds().width / 2, enemy->getBounds().height / 2),0, (this->wand->getWandLvl() + 1) * 15.f));
					this->score += enemy->score;
				}
			}
		}
		for (auto& enemy2 : this->enemies2) {
			enemy2->timeDmg = enemy2->delayDmg.getElapsedTime();
			//std::cout << bullet->getBounds().intersects(enemy->getBounds()) << "\n";
			if (bullet->getBounds().intersects(enemy2->getBounds())) {
				enemy2->damageEnemy(10.f * (this->wand->getWandLvl() + 1));
				check = true;
				if (enemy2->getEnemyState()) {
					spawnfood = rand() % 100;
					if (spawnfood <= this->foodDropRate) {
						this->foods.push_back(new Foods(sf::Vector2f(enemy2->getEnemyPos() + sf::Vector2f(enemy2->getBounds().width / 2, enemy2->getBounds().height / 2))));
						this->foodDropRate = 10;
					}
					else {
						this->foodDropRate += 5;
					}
					this->exps.push_back(new EXP(enemy2->getEnemyPos() + sf::Vector2f(enemy2->getBounds().width / 2, enemy2->getBounds().height / 2), 0, (this->wand->getWandLvl() + 1) * 10.f));
					this->score += enemy2->score;
				}
			}
		}
		for (auto& boss : this->boss) {
			boss->timeDmg = boss->delayDmg.getElapsedTime();
			//std::cout << bullet->getBounds().intersects(enemy->getBounds()) << "\n";
			if (bullet->getBounds().intersects(boss->getBounds())) {
				boss->damageEnemy(10.f * (this->wand->getWandLvl() + 1));
				check = true;
				if (boss->getEnemyState()) {
					spawnfood = rand() % 100;
					if (spawnfood <= this->foodDropRate) {
						this->foods.push_back(new Foods(sf::Vector2f(boss->getEnemyPos() + sf::Vector2f(boss->getBounds().width / 2, boss->getBounds().height / 2))));
						this->foodDropRate = 10;
					}
					else {
						this->foodDropRate += 5;
					}
					this->exps.push_back(new EXP(boss->getEnemyPos() + sf::Vector2f(boss->getBounds().width / 2, boss->getBounds().height / 2), 0, (this->wand->getWandLvl() + 1) * 120.f));
					this->score += boss->score;
				}
			}
		}
		if (check) {
			this->bullets.erase(this->bullets.begin() + counter);
			counter--;
		}
		counter++;
	}
}

void gameEngine::updateCheckEnemyAndPlayer()
{
	for (auto& enemy : this->enemies) {	
		this->player->invisTime = this->player->invisClock.getElapsedTime();
		if (this->player->invisTime.asMilliseconds() > this->player->invis && this->player->invisState) {
			this->player->invisState = false;
			this->player->invisClock.restart();
		}
		if (enemy->getEnemyAtk() && !this->player->invisState) {
			this->playerDmgTime = this->playerDmgClock.getElapsedTime();
			if (this->playerDmgTime.asMilliseconds() > 2000) {
				this->player->damagedPlayer(enemy->enemyDmg);
				this->player->invisState = true;
				this->playerDmgClock.restart();
			}
		}
		//std::cout << this->player->invisTime.asMilliseconds()  << " " << this->player->invisState << " " << "Atk!\n";
	}
	for (auto& enemy : this->enemies2) {
		this->player->invisTime = this->player->invisClock.getElapsedTime();
		if (this->player->invisTime.asMilliseconds() > this->player->invis && this->player->invisState) {
			this->player->invisState = false;
			this->player->invisClock.restart();
		}
		if (enemy->getEnemyAtk() && !this->player->invisState) {
			this->playerDmgTime = this->playerDmgClock.getElapsedTime();
			if (this->playerDmgTime.asMilliseconds() > 2000) {
				this->player->invisState = true;
				this->player->damagedPlayer(enemy->enemyDmg);
				this->playerDmgClock.restart();
			}
		}
		//std::cout << this->player->invisTime.asMilliseconds()  << " " << this->player->invisState << " " << "Atk!\n";
	}

	for(auto& boss : this->boss){
		this->player->invisTime = this->player->invisClock.getElapsedTime();
		if (this->playerDmgTime.asMilliseconds() > this->player->invis && this->player->invisState) {
			this->player->invisState = false;
			this->player->invisClock.restart();
		}
		if (boss->getEnemyAtk() && !this->player->invisState) {
			this->playerDmgTime = this->playerDmgClock.getElapsedTime();
			if (this->playerDmgTime.asMilliseconds() > 2000) {
				this->player->invisState = true;
				this->player->damagedPlayer(boss->enemyDmg);
				this->playerDmgClock.restart();
			}
		}
	}
	//std::cout << this->player->getPlayerHealth() << "\n";
}

void gameEngine::updateCheckExpAndPlayer()
{
	unsigned exp_counter = 0;
	bool check = false;
	for (auto& exp : this->exps) {
		if(this->player->getGlobalBounds().intersects(exp->getGlobalBound())) {
			this->exp_cnt++;
			check = true;
		}
		if (check) {
			this->exps.erase(this->exps.begin() + exp_counter);
			exp_counter--;
			check = false;
			this->exp_cnt++;
			this->wand->addWandLvl(exp->getAmount());
		}
		exp_counter++;
	}
}

void gameEngine::updateCheckFoodAndPlayer()
{
	unsigned food_counter = 0;
	bool check = false;
	for (auto& food : this->foods) {
		if (this->player->getGlobalBounds().intersects(food->getGlobalBounds())) {
			check = true;
		}
		if (check) {
			this->player->HealedPlayer(food->getHealAmount());
			this->foods.erase(this->foods.begin() + food_counter);
			food_counter--;
			check = false;
		}
		food_counter++;
	}
}

void gameEngine::updateTimer()
{
	this->gameTime = this->gameClock.getElapsedTime();
	//std::cout << this->gameTime.asSeconds() << "\n";
}

void gameEngine::updateInput()
{
	this->timeBullet = this->clockBullet.getElapsedTime();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if(this->timeBullet.asMilliseconds() > this->fireRate)
		{
			//std::cout << "Fire!\n" << this->timeBullet.asMilliseconds() << "\n";
			float rotation = this->wand->returnWandTarget();
			float x = this->wand->returnWandDirection().x;
			float y = this->wand->returnWandDirection().y;
			float pos_x = this->player->returnPlayerPos().x + this->player->returnPlayerCenter().x * 1.5f;
			float pos_y = this->player->returnPlayerPos().y + this->player->returnPlayerCenter().y * 1.5f;
			this->bullets.push_back(new Bullet(this->textures["Bullet"], pos_x, pos_y, x, y, rotation));
			this->Sound.play();
			this->clockBullet.restart();
		}
	}
}

void gameEngine::updateView()
{
	this->view.setCenter(this->player->returnPlayerPos().x + this->player->returnPlayerCenter().x, this->player->returnPlayerPos().y + this->player->returnPlayerCenter().y);
	this->window->setView(this->view);
}

void gameEngine::updateBullets()
{
	unsigned counter = 0;
	for (auto* i : this->bullets) {
		i->setScale(1.f + (float)this->wand->getWandLvl() / 10, 1.f + (float)this->wand->getWandLvl() / 10);
		i->updateBullet();

		//delete bullet when out of screen
		if (this->view.getCenter().x - this->view.getSize().x / 2 > i->getBounds().left + i->getBounds().width
			|| this->view.getCenter().x + this->view.getSize().x / 2 < i->getBounds().left 
			|| this->view.getCenter().y - this->view.getSize().y / 2 > i->getBounds().top + i->getBounds().height
			|| this->view.getCenter().y + this->view.getSize().y / 2 <  i->getBounds().top ) {
			this->bullets.erase(this->bullets.begin() + counter);
			counter--;

			//std::cout << "del!";
		}
		counter++;
	}
}

void gameEngine::updateSpawnPoint()
{
	float x = this->view.getSize().x;
	float y = this->view.getSize().y;
	float player_posx = this->player->returnPlayerPos().x;
	float player_posy = this->player->returnPlayerPos().y;

	this->spawnPoint[0] = { player_posx - x / 4,player_posy + y };
	this->spawnPoint[1] = { player_posx,player_posy + y };
	this->spawnPoint[2] = { player_posx + x / 4,player_posy + y };
	this->spawnPoint[3] = { player_posx - x / 4,player_posy - y };
	this->spawnPoint[4] = { player_posx,player_posy - y };
	this->spawnPoint[5] = { player_posx + x / 4,player_posy - y };
	this->spawnPoint[6] = { player_posx + x ,player_posy - y / 4 };
	this->spawnPoint[7] = { player_posx + x ,player_posy };
	this->spawnPoint[8] = { player_posx + x ,player_posy + y / 4 };
	this->spawnPoint[9] = { player_posx - x ,player_posy - y / 4 };
	this->spawnPoint[10] = { player_posx - x ,player_posy };
	this->spawnPoint[11] = { player_posx - x ,player_posy + y / 4 };
}

void gameEngine::updateEnemies()
{	
	unsigned enemies_counter = 0;
	for (auto* enemy : this->enemies) {
		enemy->updateEnemies(sf::Vector2i((int)this->player->returnPlayerPos().x + 8.f, (int)this->player->returnPlayerPos().y - this->player->returnPlayerCenter().y));

		//del enemy if isDead == true;
		if (enemy->getEnemyState() == true) {
			this->enemies.erase(this->enemies.begin() + enemies_counter);
			this->kill_counter++;
			enemies_counter--;
			this->cntSpawn--;
		}
		enemies_counter++;
	}

	unsigned enemies_counter2 = 0;
	for (auto* enemy : this->enemies2) {
		enemy->updateEnemies(sf::Vector2i((int)this->player->returnPlayerPos().x + 8.f, (int)this->player->returnPlayerPos().y - this->player->returnPlayerCenter().y));

		//del enemy if isDead == true;
		if (enemy->getEnemyState() == true) {
			this->enemies2.erase(this->enemies2.begin() + enemies_counter2);
			this->kill_counter++;
			enemies_counter2--;
			this->cntSpawn--;
		}
		enemies_counter2++;
	}

	unsigned enemies_counter3 = 0;
	for (auto* boss : this->boss) {
		boss->updateEnemies(sf::Vector2i((int)this->player->returnPlayerPos().x + 8.f, (int)this->player->returnPlayerPos().y - this->player->returnPlayerCenter().y));

		//del enemy if isDead == true;
		if (boss->getEnemyState()) {
			this->boss.erase(this->boss.begin() + enemies_counter3);
			enemies_counter3--;
			this->isBossSpawn = false;
		}
		enemies_counter3++;
	}
}

void gameEngine::updateGUI()
{	
	this->HP.setPosition(sf::Vector2f(this->player->returnPlayerPos().x + 56.f - (this->view.getSize().x / 2), this->player->returnPlayerPos().y + 78.f - (this->view.getSize().y / 2)));
	this->BHP.setPosition(sf::Vector2f(this->player->returnPlayerPos().x + 50.f - (this->view.getSize().x / 2), this->player->returnPlayerPos().y + 70.f - (this->view.getSize().y / 2)));
	float xHp = (this->player->getPlayerHealth() / this->player->getPlayerMaxHealth());
	//std::cout << xHp << "\n";
	this->exp.setPosition(sf::Vector2f(this->player->returnPlayerPos().x + 56.f - (this->view.getSize().x / 2), this->player->returnPlayerPos().y + 118.f - (this->view.getSize().y / 2)));
	this->bexp.setPosition(sf::Vector2f(this->player->returnPlayerPos().x + 50.f - (this->view.getSize().x / 2), this->player->returnPlayerPos().y + 110.f - (this->view.getSize().y / 2)));
	float xexp = (this->wand->getWandExp() / this->wand->getMaxWandExp());
	//xexp = 1.0f;
	//std::cout << this->wand->getWandExp() << " " << this->wand->getMaxWandExp() << "\n";
	
	if (xHp < 0.f) {
		xHp = 0.f;
	}
	this->HP.setScale(xHp, 1.f);
	this->exp.setScale(xexp, 1.f);

	if (score > 999999) {
		this->score = 999999;
	}
	this->score_ss.str("");
	this->score_ss << this->score;
	this->scoreText.setString(this->score_ss.str());
	this->scoreText.setPosition(sf::Vector2f(this->player->returnPlayerPos().x + 56.f - (this->view.getSize().x / 2), this->player->returnPlayerPos().y + 38.f - (this->view.getSize().y / 2)));
}

void gameEngine::Update()
{
	this->pollEvent();

	this->updateDt();

	if (this->inMenu || this->inDeadMenu || this->isPause || this->About || this->leaderBoard || this->entername) {
		this->updateMenu();
	}
	
	this->updateSound();

	if (this->play) {
		//this->player->damagedPlayer(10.f);

		//std::cout << this->player->returnPlayerPos().x << " " << this->player->returnPlayerPos().y << "\n";

		this->updateCheckBulletAndEnemies();

		this->updateCheckEnemyAndPlayer();

		this->updateCheckExpAndPlayer();

		this->updateCheckFoodAndPlayer();

		this->updateTimer();

		this->updateSpawnPoint();

		this->updateView();

		this->updateGUI();

		this->updateInput();

		this->SpawnEnemies();

		this->updateEnemies();

		this->isDead = this->player->getPlayerState();

		this->player->updatePlayer(this->ev);

		this->wand->updateWand(*this->window, this->player->returnPlayerPos());

		this->updateBullets();

		if (this->isDead) {
			this->OverSound.play();
			this->BGSound.setVolume(0.f);
			this->inDeadMenu = true;
			this->play = false;
			this->Dmenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
			this->menu = new Menu(this->window->getSize().x, this->window->getSize().y);
			this->Amenu = new AboutMenu(this->window->getSize().x, this->window->getSize().y);
			this->Lmenu = new LeaderMenu(this->window->getSize().x, this->window->getSize().y);
			this->Emenu = new InputnameMenu(this->window->getSize().x, this->window->getSize().y);
			if (this->checkPause == false)
			{
				this->MenuBG.setPosition(sf::Vector2f(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2));
				this->menu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
				this->Amenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
				this->Lmenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
				this->Emenu->setPos(this->player->returnPlayerPos().x - this->view.getSize().x / 2, this->player->returnPlayerPos().y - this->view.getSize().y / 2);
			}
		}
		else this->BGSound.setVolume(100.f);
	}
}

void gameEngine::renderGUI()
{
	this->window->draw(this->BHP);
	this->window->draw(this->HP);

	this->window->draw(this->bexp);
	this->window->draw(this->exp);

	this->window->draw(this->scoreText);
	//std::cout << this->player->returnPlayerPos().x << " " << this->player->returnPlayerPos().y << "\n";
}

void gameEngine::Render()
{
	this->window->clear(sf::Color(0,0,0,255));
	
	//std::cout << this->inMenu << "\n";

	if(this->play || this->isPause) {
		this->map.renderTilemap(*this->window, this->player->returnPlayerPos(), this->view.getSize());

		this->wand->renderWand(*this->window);

		this->player->renderPlayer(*this->window);

		for (auto* enemy : this->enemies) {
			enemy->renderEnemies(*this->window);
		}

		for (auto* enemy : this->enemies2) {
			enemy->renderEnemies(*this->window);
		}

		for (auto* enemy : this->boss) {
			enemy->renderEnemies(*this->window);
		}

		for (auto* exp : this->exps) {
			exp->renderExp(*this->window);
		}

		for (auto* i : this->bullets) {
			i->renderBullet(*this->window);
		}

		for (auto* food : this->foods) {
			food->renderFood(*this->window);
		}

		this->renderGUI();
	}

	if (this->isPause) {
		this->window->draw(this->PauseMenuBG);
		this->Pmenu->renderMenu(*this->window);
	}

	if (this->inMenu) {
		this->window->draw(this->MenuBG);
		this->menu->renderMenu(*this->window);
	}

	if (this->About) {
		this->window->draw(this->MenuBG);
		this->Amenu->renderMenu(*this->window);
	}

	if (this->leaderBoard) {
		this->window->draw(this->MenuBG);
		this->Lmenu->renderMenu(*this->window);
	}

	if (this->inDeadMenu) {
		this->window->draw(this->DeadMenuBG);
		this->Dmenu->renderMenu(*this->window);
	}

	if (this->entername) {
		this->window->draw(this->MenuBG);
		this->name.setPosition(sf::Vector2f(this->view.getCenter().x, this->view.getCenter().y  - this->view.getSize().y / 3));
		this->Ename.setPosition(sf::Vector2f(this->view.getCenter().x - this->view.getSize().x / 3, this->view.getCenter().y));
		this->Ename.setString(this->Emenu->getName());
		this->window->draw(this->name);
		this->window->draw(this->Ename);
	}
	this->window->display();
}