#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"


typedef std::vector<uGE::Mesh*> Anim;

namespace uGE{

    class Body;
    class PlayerController;
    class Player : public GameObject
    {
        private:
			float _timeCrumb = 0;
            int health = 100;
            int maxHealth = 150;
            int _shootable;
            int _score;
            float _timeLeft;
            PlayerController* _controller;

        public:
            Player();
            virtual ~Player();
            //add public stuff underneath
            int getHealth();
            void setHealth(int value);
            void addScore( int value );
            int getScore();
            int getTimeLeft();
            void resetTime();

            void changeHealth(int _health);
            void changeShootable(int value);
            int getShootable();

            void update();
            void playNow( std::string action );
            void updateFrame();

            void addCrumbs();
            void dropCrumbs();
            std::vector<glm::vec3> getCrumbs();
            std::vector<glm::vec3> crumbs;

        protected:
            Body * _body;

        private:
            float time;
            unsigned int frame = 0;
            std::string activeAction;
            Anim idle;
            Anim walk;
            Anim melee;
            Anim shoot;
            Anim suck;
            Anim death;
            Anim currentAnim;
    };
}
#endif // PLAYER_H
