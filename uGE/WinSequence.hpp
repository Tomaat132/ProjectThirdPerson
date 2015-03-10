#ifndef WINSEQUENCE_H
#define WINSEQUENCE_H
#include <SFML/Window.hpp>
#include "Game.hpp"

namespace uGE {
    class WinSequence
    {
        protected:
            sf::Window * _window;
        public:
            WinSequence();
            virtual ~WinSequence();
        private:
    };
}
#endif // WINSEQUENCE_H
