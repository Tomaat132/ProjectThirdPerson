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
			GameObject * _followee;
            Zombie * _zombieParent;

			enum State {IDLE, CHASE, TRANSFORM};
			State _state;

			//timers
			float _idleTimer;
			float _transformTimer;
			float _transformIntervalTimer;
			float _speed;
			int _eightDir;
            bool disableHitbox = false;

        public:
        //public constructor and functions
            ZombieController( GameObject * parent, GameObject * followee );
            virtual ~ZombieController();
            //add stuff underneath here

            void update();
            void move( int aDir);
            void healthCheck();

            void checkPlayerRange();
            void chaseCrumb(glm::vec3 crumb);

            void onCollision( CollisionResult * result );

        protected:
        //able to see as in public but unusable


    };

}//end of uGE
#endif // ZOMBIECONTROLLER_H
