#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <map>


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Player.h"
#include "Wands.h"
#include "Bullet.h"
#include "Tilemap.h"
#include "enemies.h"
#include "enemies2.h"
#include "Bosses.h"
#include "EXP.h"
#include "Foods.h"
#include "Menu.h"
#include "DeadMenu.h"
#include "PauseMenu.h"
#include "AboutMenu.h"
#include "LeaderBoard.h"
#include "InputnameMenu.h"
#include <fstream>

class gameEngine
{
private :

	//Window
	sf::RenderWindow* window;
	sf::VideoMode videomode;
	sf::Event ev;
	sf::View view;

	//Player
	Player *player;
	sf::Texture* GUITexture;
	sf::Texture* GuITexture2;
	sf::Clock playerDmgClock;
	sf::Time playerDmgTime;
	bool isDead;
	sf::RectangleShape DeadMenuBG;
	sf::RectangleShape PauseMenuBG;
	//Hp bar
	sf::IntRect HPRect;
	sf::IntRect BHPRect;
	sf::RectangleShape HP;
	sf::RectangleShape BHP;

	sf::RectangleShape exp;
	sf::RectangleShape bexp;

	//game timer
	sf::Clock gameClock;
	sf::Time gameTime;


	//Wand
	Wands *wand;

	//Bullet
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	sf::Clock bulletClock;
	sf::Time bulletTime;
	int fireRate;

	//Enemies
	std::pair<float,float> spawnPoint[12];
	std::map<std::string, sf::Texture*> enemies_texture;
	
	//Exps
	std::vector<EXP*> exps; 
	unsigned exp_cnt;

	//Foods
	std::vector<Foods*> foods;
	float foodDropRate;

	//Enemies
	std::vector<Enemies*> enemies;
	std::vector<Enemies2*> enemies2;
	std::vector<Bosses*> boss;
	sf::Clock enemyClock;
	sf::Time enemyTime;
	int spawnRate;
	int maxSpawn;
	int cntSpawn;
	bool isBossSpawn;

	//score
	float score;
	sf::Font font;
	std::stringstream score_ss;
	sf::Text scoreText;

	//Menu
	Menu* menu;
	DeadMenu* Dmenu;
	PauseMenu* Pmenu;
	AboutMenu* Amenu;
	LeaderMenu* Lmenu;
	InputnameMenu* Emenu;
	sf::RectangleShape MenuBG;
	bool inMenu;
	bool play;
	bool leaderBoard;
	bool About;
	bool inDeadMenu;
	bool isPause;
	bool checkPause;
	bool entername;
	int keypressed;
	int Dkeypressed;
	int Pkeypressed;
	int Akeypressed;
	int Lkeypressed;


	//Tile map
	TileMap map;
	bool isRenderTile;

	//Game Logic
	bool endgame;
	sf::Clock clockBullet;
	sf::Time timeBullet;
	sf::Clock dtClock;
	sf::Text name;
	sf::Text Ename;
	float dt;

	//cnt kill
	unsigned kill_counter;

	//sound
	sf::SoundBuffer buffer;
	sf::Sound Sound;
	sf::SoundBuffer BGbuffer;
	sf::Sound BGSound;
	sf::SoundBuffer Overbuffer;
	sf::Sound OverSound;

	//Private function
	void initVariables();
	void initWindow();
	void initView();
	void initObject();
	void initGUI();
	void initMenu();
	void initSound();
	void restart();

public :
	gameEngine();
	virtual ~gameEngine();

	const bool running() const;
	const bool getEndgame() const;
	//public function

	void pollEvent();
	void SpawnEnemies();

	//Update function
	void updateDt();
	void updateMenu();
	void updateSound();
	void updateCheckBulletAndEnemies();
	void updateCheckEnemyAndPlayer();
	void updateCheckExpAndPlayer();
	void updateCheckFoodAndPlayer();
	void updateTimer();
	void updateInput();
	void updateView();
	void updateBullets();
	void updateSpawnPoint();
	void updateEnemies();
	void updateGUI();
	void Update();

	//Render function
	void renderGUI();
	void Render();
};

