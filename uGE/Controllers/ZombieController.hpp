#ifndef ZOMBIECONTROLLER_H
#define ZOMBIECONTROLLER_H

#include "Controller.hpp"

#include "GameObject.hpp"

#include "Zombie.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"

#include "utils/glm.hpp"
#include "string.h"

namespace uGE{

    class Zombie;
    class ZombieController : public Controller
    {
        private:
        //private variables
        Zombie* _parent;
        GameObject* _followee;
        enum State {IDLE, TRANSFORM};
        State _state;
        //timers
        float _idleTimer;
        float _transformTimer;
        float _transformIntervalTimer;
        float _speed;
        int _eightDir;

        public:
        //public constructor and functions
            ZombieController(uGE::Zombie * parent, uGE::GameObject * followee);
            virtual ~ZombieController();
            //add stuff underneath here

            void update();
            void move( int aDir);
            void healthCheck();
            void onCollision( CollisionResult* result);
        protected:
        //able to see as in public but unusable

        private:
        //don't let other mess with yo stuff


    };

}//end of uGE
#endif // ZOMBIECONTROLLER_H
