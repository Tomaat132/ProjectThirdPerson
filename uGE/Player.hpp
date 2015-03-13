#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"

namespace uGE{

    class Player : public GameObject
    {
        private:
			float _timeCrumb = 0;
            int health = 100;
            int maxHealth = 150;
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

            void addCrumbs();
            void dropCrumbs();
            std::vector<glm::vec3> getCrumbs();
            std::vector<glm::vec3> crumbs;

        protected:

    };
}
#endif // PLAYER_H
