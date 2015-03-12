#ifndef MENU_H
#define MENU_H
#include <SFML/Window.hpp>

#include "Body.hpp"
#include "GameObject.hpp"

namespace uGE {

	class GameObject;
	class Shader;

	class Menu
	{
		protected:
			sf::Window * _window;
		public:
			Menu();
			virtual ~Menu();

			virtual bool load() = 0;
			bool run();
	};
}
#endif // MENU_H
