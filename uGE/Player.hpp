#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include "Utils/glm.hpp"

#include <map>

typedef std::vector<uGE::Mesh*> Anim;

namespace uGE{

    class Body;

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
            float time = 0.f;
            unsigned int frame = 0;
            Anim idle;
            Anim walk;
            Anim currentAnim;
    };
}
#endif // PLAYER_H
