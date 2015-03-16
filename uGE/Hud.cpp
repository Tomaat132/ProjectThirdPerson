#include <GL/glew.h>
#include <string>
#include <iostream>

#include "SceneManager.hpp"
#include "Player.hpp"
#include "Viking.hpp"
#include "ZombieSpawnController.hpp"
#include "Hud.hpp"
#include "Logger.h"

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

        zombieText.setString( to_s( Viking::zombieCount ) );
        healthText.setString( to_s( SceneManager::_player->getHealth() ) );
        spiritText.setString( to_s( SceneManager::_player->getShootable() ) );

        window->draw( zombieText );
        window->draw( healthText );
        window->draw( spiritText );

        window->popGLStates();
        glEnable( GL_CULL_FACE );
    }

}
