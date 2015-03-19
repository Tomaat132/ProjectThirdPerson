#include "SoundManager.hpp"
#include <SFML/Audio.hpp>

#include <iostream>
#include <iomanip>
#include "Logger.h"

namespace uGE
{

    bool SoundManager::active = false;
    sf::Music * SoundManager::bgm;
    std::vector<sf::Sound*> SoundManager::sounds;
    std::map<std::string,sf::SoundBuffer*> SoundManager::soundMap;

    void SoundManager::init()
    {
        sounds.clear();
        soundMap.clear();

        getSFX("Rifle");
        getSFX("Launch");
        getSFX("Sucking");
        getSFX("Zombie");
        getSFX("ZombieDie");
        getSFX("PlayerHit");
        getSFX("PlayerAtk");
        getSFX("SpiritCollect");
        for( unsigned int i = 0; i < 64; ++i ) {
            sounds.push_back( new sf::Sound );
        }

        active = true;
    }

    void SoundManager::getBGM(std::string iFilename)
    {
        if( !active ) {
            Logger::print( Logger::WARNING, "Sound Manager is not yet initialized. Could not play sounds." );
            return;
        }

        bgm = new sf::Music;
        if (!bgm->openFromFile("Assets/Music/" + iFilename + ".wav"))
        {
            Logger::print( Logger::ERROR, "Error loading " + iFilename );
            return;
        }
        bgm->play();
        bgm->setLoop(true);
    }//end of getBGM function

    void SoundManager::getSFX(std::string iFilename)
    {
        sf::SoundBuffer * buffer = new sf::SoundBuffer;
        if (!buffer->loadFromFile("Assets/Music/Fx/" + iFilename + ".wav"))
        {
            Logger::print( Logger::ERROR, "Error loading " + iFilename );
            return;
        }
        soundMap[ iFilename ] = buffer;
    }//end of getSFX function;

    void SoundManager::playSFX(std::string iFilename)
    {
        if( !active ) {
            Logger::print( Logger::WARNING, "Sound Manager is not yet initialized. Could not play sounds." );
            return;
        }

        auto found = soundMap.find( iFilename );
        if( found == soundMap.end() ) {
            Logger::print( Logger::ERROR, "SFX not found: " + iFilename );
            return;
        }

        unsigned int soundPos = findFreeSound();
        if( soundPos == sounds.size() ) {
            Logger::print( Logger::WARNING, "No free sounds! Could not play " + iFilename );
            return;
        }

        sf::Sound * sound = sounds[ soundPos ];
        sound->setBuffer( *soundMap[ iFilename ] );
        sound->play();
    }

   unsigned int SoundManager::findFreeSound()
   {
        for( unsigned int i = 0; i < sounds.size(); i++ ){
           if( sounds[i]->getStatus() == sf::SoundSource::Stopped ){
               return i;
           }
        }
        return sounds.size();
    }

}
