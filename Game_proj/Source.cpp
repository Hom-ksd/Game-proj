#include "gameEngine.h"

int main() {

	gameEngine game;

	sf::Clock clock;

	while (game.running() == !game.getEndgame()) {
		float currentTime = clock.restart().asSeconds();
		float fps = 1.0f / (currentTime); 
		//std::cout << game.running() << " " << game.getEndgame() << "\n";
		//std::cout << "fps :  " << fps << std::endl;
		
		//Update game
		game.Update();

		//Render game
		game.Render();
	}
	//std::cout << "End!\n";
	return 0;
}