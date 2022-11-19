#include "TileMap.h"

void TileMap::initTilemap()
{
	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; x++) {

		this->map.push_back(std::vector<std::vector<Tile*>>());

		for (size_t y = 0; y < this->maxSize.y; y++) {

			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
			this->map[x].push_back(std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++) {
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}
	this->tileTextureSheet.loadFromFile("style_sheet/Tiles/full_tilemap.png");
}

void TileMap::addTile()
{
	srand(time(NULL));
	sf::IntRect rect;
	int p = 16;
	int cnt_on_wall = 25;
	for (size_t x = 0; x < this->maxSize.x; x++) {
		for (size_t y = 0; y < this->maxSize.y; y++) {
			for (size_t z = 0; z < this->layers; z++) {
				if (this->map[x][y][z] == NULL) {
					if (z == 0) {
						if (y == 0) {
							if (x == 0) {
								rect = sf::IntRect(p * 4, p * 4, p, p);
							}
							else if(x == this->maxSize.x - 1) {
								rect = sf::IntRect(p * 3, p * 4, p, p);
							}
							else {
								rect = sf::IntRect(p * 2, p * 7, p, p);
							}
						}
						else if (x == 0) {
							rect = sf::IntRect(p * 4, p * 5, p, p);
						}
						else if (x == this->maxSize.x - 1) {
							rect = sf::IntRect(p * 3, p * 5, p, p);
						}
						else if (y == 1) {
							int x = rand() % 3 + 6;
							int y = rand() % 2 + 4;
							rect = sf::IntRect(p * x, p * y, p, p);
						}
						else {
							int x = rand() % 4 + 2;
							int y = rand() % 3 + 1;
							if (y == 1 && (x == 4 || x == 5)) {
								y++;
							}
							rect = sf::IntRect(x * p, y * p, p, p);
						}
					}
					else {
						if (y == 1 && (x != 0 && x != this->maxSize.x - 1) && cnt_on_wall > 0) {
							int y = rand() % 2;
							int x;
							if (y == 1) {
								x = 7;
								y = 2;
							}
							else x = rand() % 2 + 3;
							rect = sf::IntRect(x * p, y * p, p, p);
						}
					}
					this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF,this->gridSizeF,this->tileTextureSheet,rect);
				}
			}
		}
	}
}

TileMap::TileMap()
{
	this->gridSizeF = 80.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = 100;
	this->maxSize.y = 100;
	this->layers = 2;
	this->initTilemap();
	this->addTile();
}


void TileMap::renderTilemap(sf::RenderTarget& target,sf::Vector2i playerPos,sf::Vector2f viewSize)
{
	for (auto& x : this->map) {
		for (auto& y : x) {
			for (auto& z : y) {
				if (z != NULL) {
					if ((z->getTilePos().x >= playerPos.x - viewSize.x / 2 - 160 && z->getTilePos().x <= playerPos.x + viewSize.x / 2 + 160) && (z->getTilePos().y >= playerPos.y - viewSize.y / 2 - 160 && z->getTilePos().y <= playerPos.y + viewSize.y / 2 + 160))
						z->renderTile(target); 
				}
				//std::cout << "0";
			}
		}
	}
}


