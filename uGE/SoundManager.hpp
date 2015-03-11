#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <SFML/Audio.hpp>


namespace uGE{
    class SoundManager
    {
        public:
            SoundManager();
            virtual ~SoundManager();

            static std::vector<sf::Sound *> sounds;
            static std::vector<sf::SoundBuffer *> buffers;

            void getBGM(std::string iFilename);
            void getSFX(std::string iFilename);

            void playSFX(std::string iFilename);
            unsigned int findFreeSound();

        protected:
        private:

            sf::Music *bgm;
            sf::SoundBuffer *buffer;
            sf::Sound *sfx;



    };
}
#endif // SOUNDMANAGER_H
