#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"


namespace uGE{

    class Player : public GameObject
    {
        public:
            Player();
            virtual ~Player();
            //add public stuff underneath
            int getHealth();

            void changeHealth(int _health);
            void update();

        protected:
        private:

            int health = 100;
            int maxHealth = 150;
    };
}
#endif // PLAYER_H
