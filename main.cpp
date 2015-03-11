#include <iostream>

#include "MyGame.hpp"
#include "uGE/CollisionDetection.hpp"

int main()
{
	MyGame * game = new MyGame();
	game->load();
	game->run();

	return 0;
}
