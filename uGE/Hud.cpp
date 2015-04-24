#include <GL/glew.h>
#include <string>
#include <iostream>

#include "SceneManager.hpp"
#include "Player.hpp"
#include "Viking.hpp"
#include "ZombieSpawnController.hpp"
#include "Hud.hpp"
#include "Logger.h"
#include "Time.hpp"

namespace uGE
{

    Hud::Hud()
    : gameEnd( false ), gamePaused( true ), endAlpha( 0.f ), endAlpha2( 0.f ), scoreCounter( 0 )
    {
        healthImg.loadFromFile( "Assets/Textures/Hud/life hud.png" );
        spiritImg.loadFromFile( "Assets/Textures/Hud/spirit hud.png" );
        timeImg.loadFromFile( "Assets/Textures/Hud/time hud.png" );
        scoreImg.loadFromFile( "Assets/Textures/Hud/score hud.png" );
        endImg.loadFromFile( "Assets/Textures/Hud/end screen thing.png" );
        startImg.loadFromFile( "Assets/Textures/Hud/Start_manual.png" );

        healthSprite.setTexture( healthImg );
        healthSprite.setPosition( 12, 20 );

        spiritSprite.setTexture( spiritImg );
        spiritSprite.setPosition( 20, 20 );

        timeSprite.setTexture( timeImg );
        timeSprite.setPosition( 20, 620 );

        scoreSprite.setTexture( scoreImg );
        scoreSprite.setPosition( 876, 640 );

        endSprite.setTexture( endImg );
        endSprite.scale( .75f, .75f );
        endSprite.setColor( sf::Color( 255, 255, 255, 0 ) );
        endSprite.setPosition( 128, 96 );

        startSprite.setTexture( startImg );
        startSprite.scale( .75f, .75f );
        startSprite.setColor( sf::Color( 255, 255, 255, 1 ) );
        startSprite.setPosition( 64, 96 );

        font.loadFromFile( "Assets/VIKING-N.ttf" );

        healthText.setCharacterSize( 48 );
        healthText.setColor( sf::Color::White );
        healthText.setFont( font );
        healthText.setPosition( 52, 56 );

        waveText.setCharacterSize( 19 );
        waveText.setColor( sf::Color::White );
        waveText.setFont( font );            sf::Texture endImg;

        waveText.setPosition( 740, 30 );

        timeText.setCharacterSize( 40 );
        timeText.setColor( sf::Color::White );
        timeText.setFont( font );
        timeText.setPosition( 39, 658 );

        scoreText.setCharacterSize( 32 );
        scoreText.setColor( sf::Color::White );
        scoreText.setFont( font );
        scoreText.setPosition( 928, 694 );

        endText.setCharacterSize( 72 );
        endText.setFont( font );
        endText.setPosition( 200, 250 );
        endText.setColor( sf::Color( 255, 255, 255, 0 ) );

        endScoreText.setCharacterSize( 30 );
        endScoreText.setFont( font );
        endScoreText.setPosition( 200, 540 );
        endScoreText.setColor( sf::Color( 255, 255, 255, 0 ) );
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
        //window->draw( spiritSprite );
        window->draw( timeSprite );
        window->draw( scoreSprite );

        healthText.setString( to_s( SceneManager::_player->getHealth() ) );
        waveText.setString( "Level: "+ to_s( uGE::SceneManager::zombieLevel ) );
        timeText.setString( formatTime( SceneManager::_player->getTimeLeft() ) );
        scoreText.setString( to_s( SceneManager::_player->getScore() ) );

        drawWithOutline( &healthText, window );
        drawWithOutline( &waveText, window, sf::Color::White );
        drawWithOutline( &timeText, window );
        drawWithOutline( &scoreText, window );

        if( gameEnd ) {
            endAlpha = glm::min( 255.f, endAlpha + 100.f * Time::step() );
            if( endAlpha >= 255.f ) {
                endAlpha2 = glm::min( 255.f, endAlpha2 + 200.f * Time::step() );
                if( endAlpha2 >= 255.f ) {
                    scoreCounter = glm::min( SceneManager::_player->getScore(), scoreCounter + (int) glm::ceil( 500.f * Time::step() ) );
                }
            }

            endSprite.setColor( sf::Color( 255, 255, 255, endAlpha ) );
            endScoreText.setString( "Your score:   " + to_s( scoreCounter ) );

            window->draw( endSprite );
            drawWithOutline( &endText, window, sf::Color( 255, 255, 255, endAlpha ), 2 );
            drawWithOutline( &endScoreText, window, sf::Color( 255, 255, 255, endAlpha2 ) );
        }
        if( gamePaused ) {


            //pauseSprite.setColor( sf::Color( 255, 255, 255, endAlpha ) );

            //startSprite.setColor( sf::Color( 255, 255, 255, endAlpha ) );
            endAlpha = glm::min( 255.f, endAlpha + 100.f * Time::step() );
            if( endAlpha >= 255.f ) {
                endAlpha2 = glm::min( 255.f, endAlpha2 + 200.f * Time::step() );
                if( endAlpha2 >= 255.f ) {
                    scoreCounter = glm::min( SceneManager::_player->getScore(), scoreCounter + (int) glm::ceil( 500.f * Time::step() ) );
                }
            }
            startSprite.setColor( sf::Color( 255, 255, 255, endAlpha ) );

            window->draw( startSprite );

            //drawWithOutline( &endText, window, sf::Color( 255, 255, 255, endAlpha ), 2 );
            //drawWithOutline( &endScoreText, window, sf::Color( 255, 255, 255, endAlpha2 ) );
        }

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


    void Hud::drawWithOutline( sf::Text* text, sf::RenderWindow* window, sf::Color color, int lineSize )
    {
        sf::Color backColor = sf::Color::Black;
        backColor.a = color.a;

        text->setColor( backColor );
        text->move( -lineSize, -lineSize );
        window->draw( *text );
        text->move( 2 * lineSize, 0 );
        window->draw( *text );
        text->move( -2 * lineSize, 2 * lineSize );
        window->draw( *text );
        text->move( 2 * lineSize, 0 );
        window->draw( *text );
        text->move( -lineSize, -lineSize );

        text->setColor( color );
        window->draw( *text );
    }


    void Hud::setEndGame( std::string text ) {
        gameEnd = true;
        endText.setString( text );

        SceneManager::paused = true;
    }

    void Hud::setPause(){
        gamePaused = !gamePaused;
        //SceneManager::paused = gamePaused;

    }
}
