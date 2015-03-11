#include "SoundManager.hpp"
#include <SFML/Audio.hpp>

#include <iostream>
#include <iomanip>

namespace uGE
{
    std::vector<sf::Sound*> SoundManager::sounds;
    std::vector<sf::SoundBuffer *> SoundManager::buffers;

    SoundManager::SoundManager()
    {
        //ctor
        getSFX("rifle");
        getSFX("Launch");

    }

    SoundManager::~SoundManager()
    {
        //dtor
    }
    //add stuf below here

    void SoundManager::getBGM(std::string iFilename)
    {
        bgm = new sf::Music;
        if (!bgm->openFromFile("Assets/Music/" + iFilename + ".wav"))
        {
            std::cout<< "#$#$# error loading: "<< iFilename<< std::endl;
        }
        bgm->play();
    }//end of getBGM function

    void SoundManager::getSFX(std::string iFilename){
    buffer = new sf::SoundBuffer;
    buffers.push_back(buffer);
        //std::cout<<buffers.size()<< " buffer size" <<std::endl;

    if (!buffer->loadFromFile("Assets/Music/Fx/" + iFilename + ".wav"))
        {
            std::cout<< "#$#$# error loading: "<< iFilename<< " sound effect " << std::endl;
        }
    }//end of getSFX function;

    void SoundManager::playSFX(std::string iFilename){
        //getSFX(iFilename);
        sfx = new sf::Sound;
        sounds.push_back(sfx);

        for(unsigned int i = 0; i < buffers.size() ;i++ ){
            sfx->setBuffer(*buffers[i]);

        }
        std::cout<<buffers.size()<<" sounds size" <<std::endl;
        //findFreeSound();
        sfx->play();
        }

   unsigned int SoundManager::findFreeSound(){
        for (unsigned int i = 0 ; i < sounds.size() ;i++){
            sf::Sound *aSound = sounds[i];
            std::cout<< aSound->getStatus() << std::endl;

           if(aSound->getStatus() == sf::SoundSource::Stopped){

               return i;
           }//end of if soundsource is empty

        }//end of forloop

    return 0;
    }//end of findFreeSound();


}//end of uGE namespace
