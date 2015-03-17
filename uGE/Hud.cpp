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
        healthSprite.setPosition( 448, 20 );

        spiritSprite.setTexture( spiritImg );
        spiritSprite.setPosition( 20, 20 );

        timeSprite.setTexture( timeImg );
        timeSprite.setPosition( 20, 620 );

        scoreSprite.setTexture( scoreImg );
        scoreSprite.setPosition( 876, 640 );

        font.loadFromFile( "Assets/VIKING-N.ttf" );

        healthText.setCharacterSize( 48 );
        healthText.setColor( sf::Color::White );
        healthText.setFont( font );
        healthText.setPosition( 480, 52 );

        spiritText.setCharacterSize( 40 );
        spiritText.setColor( sf::Color::White );
        spiritText.setFont( font );
        spiritText.setPosition( 52, 96 );

        timeText.setCharacterSize( 40 );
        timeText.setColor( sf::Color::White );
        timeText.setFont( font );
        timeText.setPosition( 39, 658 );

        scoreText.setCharacterSize( 32 );
        scoreText.setColor( sf::Color::White );
        scoreText.setFont( font );
        scoreText.setPosition( 936, 694 );
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
        timeText.setString( formatTime( SceneManager::_player->getTimeLeft() ) );
        scoreText.setString( to_s( SceneManager::_player->getScore() ) );

        drawWithOutline( &healthText, window );
        drawWithOutline( &spiritText, window, sf::Color::Cyan );
        drawWithOutline( &timeText, window );
        drawWithOutline( &scoreText, window );

        window->popGLStates();
        glEnable( GL_CULL_FACE );
    }


    std::string Hud::formatTime( int time )
    {
        int minutes = time / 60;
        int seconds = time % 60;

        char cTime[16];
        sprintf( cTime, "%1d:%02d", minutes, seconds );
        return std::string( cTime );
    }


    void Hud::drawWithOutline( sf::Text* text, sf::RenderWindow* window, sf::Color color )
    {
        text->setColor( sf::Color::Black );
        text->move( -1, -1 );
        window->draw( *text );
        text->move( 2, 0 );
        window->draw( *text );
        text->move( -2, 2 );
        window->draw( *text );
        text->move( 2, 0 );
        window->draw( *text );
        text->move( -1, -1 );

        text->setColor( color );
        window->draw( *text );
    }
}
