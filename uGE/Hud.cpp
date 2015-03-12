#include <GL/glew.h>
#include <string>
#include <iostream>

#include "SceneManager.hpp"
#include "Player.hpp"
#include "Viking.hpp"
#include "Hud.hpp"

namespace uGE
{

    Hud::Hud()
    {
        hudImage.loadFromFile( "Assets/Textures/Hud.png" );
        hudTexture.loadFromImage( hudImage );
        hudSprite.setTexture( hudTexture );

        font.loadFromFile( "Assets/VIKING-N.ttf" );

        zombieText.setCharacterSize( 48 );
        zombieText.setColor( sf::Color::White );
        zombieText.setPosition( 200, 20 );

        healthText.setCharacterSize( 48 );
        healthText.setColor( sf::Color::White );
        healthText.setPosition( 550, 20 );

        spiritText.setCharacterSize( 48 );
        spiritText.setColor( sf::Color::White );
        spiritText.setPosition( 920, 20 );
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

        zombieText.setFont( font );
        healthText.setFont( font );
        spiritText.setFont( font );

        char cZombies[64];
        sprintf( cZombies, "%d", Viking::zombieCount );
        zombieText.setString( cZombies );

        char cHealth[64];
        sprintf( cHealth, "%d", SceneManager::_player->getHealth() );
        healthText.setString( cHealth );

        char cSpirits[64];
        sprintf( cSpirits, "%d", SceneManager::_player->getShootable() );
        spiritText.setString( cSpirits );

        window->draw( zombieText );
        window->draw( healthText );
        window->draw( spiritText );

        window->popGLStates();
        glEnable( GL_CULL_FACE );
    }

}
