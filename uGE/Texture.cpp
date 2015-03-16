#include "Texture.hpp"

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Logger.h"

namespace uGE {

	Texture::Texture( GLuint name )
	:	_name( name )
	{
	}

	Texture::~Texture()
	{
		glDeleteTextures( 1, & _name );
	}

	GLuint Texture::getName()
	{
		return _name;
	}

	Texture * Texture::load( std::string filename )
	{
		sf::Image image;
		if ( image.loadFromFile( filename ) ) {
			image.flipVertically();
			GLuint name;
			glGenTextures( 1, &name );
				glBindTexture( GL_TEXTURE_2D, name );
					glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
					glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
//				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
				//glGenerateMipmap( GL_TEXTURE_2D ); 							// for mipmapping
				//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0 ); 	// for mipmapping
				//glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4 ); 	// for mipmapping
			if ( name != 0 ) {
				Logger::print( Logger::INFO, "Done loading texture: " + filename + " with name " + to_s(name) );
				return new Texture( name );
			}
			Logger::print( Logger::ERROR, "Error initializing texture " + filename );
		}
		Logger::print( Logger::ERROR, "Error loading texture " + filename );
		return 0;
	}
}
