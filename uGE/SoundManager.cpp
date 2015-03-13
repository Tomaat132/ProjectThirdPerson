#include "SoundManager.hpp"
#include <SFML/Audio.hpp>

#include <iostream>
#include <iomanip>

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

        getSFX("rifle");
        getSFX("Launch");

        for( unsigned int i = 0; i < 64; ++i ) {
            sounds.push_back( new sf::Sound );
        }

        active = true;
    }

    void SoundManager::getBGM(std::string iFilename)
    {
        if( !active ) {
            std::cout << "Sound Manager is not yet initialized. Could not play sounds." << std::endl;
            return;
        }

        bgm = new sf::Music;
        if (!bgm->openFromFile("Assets/Music/" + iFilename + ".wav"))
        {
            std::cout<< "#$#$# error loading: "<< iFilename<< std::endl;
        }
        bgm->play();
    }//end of getBGM function

    void SoundManager::getSFX(std::string iFilename)
    {
        sf::SoundBuffer * buffer = new sf::SoundBuffer;
        if (!buffer->loadFromFile("Assets/Music/Fx/" + iFilename + ".wav"))
        {
            std::cout<< "#$#$# error loading: "<< iFilename<< " sound effect " << std::endl;
            return;
        }
        soundMap[ iFilename ] = buffer;
    }//end of getSFX function;

    void SoundManager::playSFX(std::string iFilename)
    {
        if( !active ) {
            std::cout << "Sound Manager is not yet initialized. Could not play sounds." << std::endl;
            return;
        }

        auto found = soundMap.find( iFilename );
        if( found == soundMap.end() ) {
            std::cout << "SFX not found: " << iFilename << std::endl;
            std::cout << "# of loaded sounds: " << soundMap.size() << std::endl;
            return;
        }

        unsigned int soundPos = findFreeSound();
        if( soundPos == sounds.size() ) {
            std::cout << "No free sounds! Could not play sound: " << iFilename << std::endl;
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
