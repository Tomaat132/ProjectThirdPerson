#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"


namespace uGE{

    class Player : public GameObject
    {
        private:
            int _shootable;
            int _score;
        public:
            Player();
            virtual ~Player();
            //add public stuff underneath
            int getHealth();
            void addScore( int value );
            int getScore();

            void changeHealth(int _health);
            void update();
            void changeShootable(int value);
            int getShootable();
        protected:
        private:
    };
}
#endif // PLAYER_H
