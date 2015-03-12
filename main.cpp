#include <iostream>

#include "MyMenu.hpp"
//#include "MyGame.hpp"
#include "uGE/CollisionDetection.hpp"

int main()
{
	MyMenu * menu = new MyMenu();
	menu->load();
	menu->run();

	return 0;
}
