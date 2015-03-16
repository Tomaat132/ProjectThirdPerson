#include "Game.hpp"
#include "SceneManager.hpp"
#include "Logger.h"

namespace uGE {

	Game::Game()
	: _window ( new sf::RenderWindow( sf::VideoMode( 1024, 768 ), "Redemption"/*, sf::Style::Fullscreen*/ ) )
	{
		//_window->setVerticalSyncEnabled( true );
		Logger::print( Logger::INFO, "Init Glew: " + to_s( glewInit() ) + " - GL: " + to_s( glGetString( GL_VERSION ) ) );
        Logger::print( Logger::INFO, "Max textures size" + to_s( GL_MAX_TEXTURE_SIZE ) );
		Logger::print( Logger::INFO, "GLSL version: " + to_s( glGetString( GL_SHADING_LANGUAGE_VERSION ) ) );

		glEnable( GL_DEPTH_TEST );
		glEnable( GL_CULL_FACE );
		glEnable( GL_BLEND );
		glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	}

	Game::~Game()
	{
		_window->close();
	}

	bool Game::run()
	{
		bool running = true;
		while ( running ) {
			running = SceneManager::control( _window );
			SceneManager::update();
			SceneManager::render( _window );
		}
		return true;
	}
}
