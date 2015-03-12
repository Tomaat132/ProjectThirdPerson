#ifndef MYMENU_H
#define MYMENU_H

#include "uGE\MainMenu\Menu.hpp"

class MyMenu : public uGE::Menu
{
	public:
		MyMenu();
		virtual ~MyMenu();

		bool load();
};

#endif // MYMENU_H
