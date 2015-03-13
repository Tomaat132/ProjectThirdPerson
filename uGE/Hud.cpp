#include <GL/glew.h>
#include <iostream>
#include "Hud.hpp"

namespace uGE
{

    Hud::Hud()
    {
        hudImage.loadFromFile( "Assets/Textures/Hud.png" );
        hudTexture.loadFromImage( hudImage );
        hudSprite.setTexture( hudTexture );
    }

    Hud::~Hud()
    {
        //dtor
    }

    void Hud::draw( sf::RenderWindow * window )
    {
        glDisable( GL_CULL_FACE );
        window->pushGLStates();

        hudSprite.setPosition( 0, 0 );
        window->draw( hudSprite );

        window->popGLStates();
        glEnable( GL_CULL_FACE );
    }

}
