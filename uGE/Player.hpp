#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.hpp"
#include <map>

typedef std::vector<uGE::Mesh*> Anim;

namespace uGE{

    class Body;

    class Player : public GameObject
    {
        public:
            Player();
            virtual ~Player();
            //add public stuff underneath
            int getHealth();

            void changeHealth(int _health);
            void update();
            void playNow( std::string action );
            void updateFrame();

        protected:
            Body * _body;
        private:
            float time = 0.f;
            unsigned int frame = 0;
            std::string activeAction;
            Anim idle;
            Anim walk;
            Anim currentAnim;
    };
}
#endif // PLAYER_H
