#include <iostream>

#include "MyGame.hpp"
#include "uGE/CollisionDetection.hpp"

int main()
{
    //cerr << "#### creating game" << endl;
	MyGame * game = new MyGame();
	//cerr << "#### created a game"<< endl;
	game->load();
	//cerr << "#### did load" << endl;
	game->run();
	//cerr << "#### leaving"<< endl;

	return 0;
}
