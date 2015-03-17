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
        healthImg.loadFromFile( "Assets/Textures/Hud/life hud.png" );
        spiritImg.loadFromFile( "Assets/Textures/Hud/spirit hud.png" );
        timeImg.loadFromFile( "Assets/Textures/Hud/time hud.png" );
        scoreImg.loadFromFile( "Assets/Textures/Hud/score hud.png" );

        healthSprite.setTexture( healthImg );
        healthSprite.setPosition( 20, 20 );

        spiritSprite.setTexture( spiritImg );
        spiritSprite.setPosition( 444, 20 );

        timeSprite.setTexture( timeImg );
        timeSprite.setPosition( 20, 500 );

        scoreSprite.setTexture( scoreImg );
        scoreSprite.setPosition( 150, 500 );

        font.loadFromFile( "Assets/VIKING-N.ttf" );

        healthText.setCharacterSize( 48 );
        healthText.setColor( sf::Color::White );
        healthText.setFont( font );
        healthText.setPosition( 50, 50 );

        spiritText.setCharacterSize( 48 );
        spiritText.setColor( sf::Color::White );
        spiritText.setFont( font );
        spiritText.setPosition( 500, 250 );

        timeText.setCharacterSize( 48 );
        timeText.setColor( sf::Color::White );
        timeText.setFont( font );
        timeText.setPosition( 50, 500 );

        scoreText.setCharacterSize( 48 );
        scoreText.setColor( sf::Color::White );
        scoreText.setFont( font );
        scoreText.setPosition( 150, 500 );
    }

    Hud::~Hud()
    {
        //dtor
    }

    void Hud::draw( sf::RenderWindow * window )
    {
        glDisable( GL_CULL_FACE );
        window->pushGLStates();

        window->draw( healthSprite );
        window->draw( spiritSprite );
        window->draw( timeSprite );
        window->draw( scoreSprite );

        healthText.setString( to_s( SceneManager::_player->getHealth() ) );
        spiritText.setString( to_s( SceneManager::_player->getShootable() ) );
        timeText.setString( to_s( SceneManager::_player->getTimeLeft() ) );
        scoreText.setString( to_s( SceneManager::_player->getScore() ) );

        window->draw( healthText );
        window->draw( spiritText );
        window->draw( timeText );
        window->draw( scoreText );

        window->popGLStates();
        glEnable( GL_CULL_FACE );
    }

}
