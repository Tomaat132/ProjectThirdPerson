#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"


namespace uGE{
    class PlayerController;
    class Player : public GameObject
    {
        private:
            int _shootable;
            int _score;
            float _timeLeft;
            PlayerController* _controller;

        public:
            Player();
            virtual ~Player();
            //add public stuff underneath
            int getHealth();
            void addScore( int value );
            int getScore();
            int getTimeLeft();
            void resetTime();

            void changeHealth(int _health);
            void update();
            void changeShootable(int value);
            int getShootable();
            //PlayerController* getPlayerController();
        protected:
        private:
    };
}
#endif // PLAYER_H
