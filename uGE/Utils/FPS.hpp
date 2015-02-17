#ifndef FPS_H
#define FPS_H

#include <SFML/System.hpp>

namespace uGE {

    class FPS
    {
        private:
            FPS(){}

        public:
            static void update();
            static unsigned int getFPS();

        private:
            static float startTime;
            static float time;
            static unsigned int count;
            static unsigned int fps;
            static sf::Clock clock;
    };
}

#endif // FPS_H
