#include <iostream>

#include "MyGame.hpp"

int main()
{
	MyGame * game = new MyGame();
	game->load();
	game->run();

	return 0;
}
