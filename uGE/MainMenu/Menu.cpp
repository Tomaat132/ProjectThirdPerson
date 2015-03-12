#include "Menu.hpp"
#include "MainMenu/MenuManager.hpp"

namespace uGE {

	Menu::Menu()
	: _window ( new sf::Window( sf::VideoMode( 1024, 768 ), "Redemption: Main Menu" /*, sf::Style::Fullscreen*/ ) )
	{
		_window->setVerticalSyncEnabled( true );
		std::cout << "Init Glew " << glewInit() << " GL : " << glGetString( GL_VERSION ) << std::endl;
		std::cout << "Max textures size " << GL_MAX_TEXTURE_SIZE << std::endl;
		std::cout << "GLSL version " << glGetString( GL_SHADING_LANGUAGE_VERSION ) << std::endl;

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );
		glEnable( GL_BLEND );
		glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	Menu::~Menu()
	{
		_window->close();
	}

	bool Menu::run()
	{
		bool running = true;
		while ( running ) {
			running = MenuManager::control( _window );
			MenuManager::update();
			MenuManager::render( _window );
		}
		return true;
	}
}
