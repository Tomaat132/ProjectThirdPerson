#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"

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

            void addCrumbs();
            void dropCrumbs();

            std::vector<glm::vec3> getCrumbs();

            std::vector<glm::vec3> crumbs;

        protected:
        private:

            float _timeCrumb = 0;



            int health = 100;
            int maxHealth = 150;
    };
}
#endif // PLAYER_H
