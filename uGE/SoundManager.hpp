#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream>
#include <map>
#include <SFML/Audio.hpp>


namespace uGE{
    class SoundManager
    {
        public:
            SoundManager();
            virtual ~SoundManager();

            static void init();

            static void getBGM(std::string iFilename);
            static void getSFX(std::string iFilename);
            static void playSFX(std::string iFilename);

        protected:
        private:
            static bool active;
            static sf::Music *bgm;
            static std::vector<sf::Sound*> sounds;
            static std::map<std::string,sf::SoundBuffer*> soundMap;

            static unsigned int findFreeSound();
    };
}
#endif // SOUNDMANAGER_H
