#include "WinSequence.hpp"
#include <GL/glew.h>
#include <iostream>

namespace uGE {

    WinSequence::WinSequence()
	: _window ( new sf::Window( sf::VideoMode( 400, 200 ), "Game Over: You won!" /*, sf::Style::Fullscreen*/ ) )
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

	WinSequence::~WinSequence()
	{
		_window->close();
	}

}
