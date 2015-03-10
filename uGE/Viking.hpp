#ifndef VIKING_H
#define VIKING_H

#include <SFML/Window.hpp>

namespace uGE {

    class Viking
    {
        public:
            Viking();
            virtual ~Viking();

            static int zombieCount;
            static void startWinSeq();
        protected:
			sf::Window * _window;
        private:
    };
}
#endif // VIKING_H
