#ifndef ZOMBIECONTROLLER_H
#define ZOMBIECONTROLLER_H

#include "Controller.hpp"

#include "GameObject.hpp"
#include "Body.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"

#include "utils/glm.hpp"

namespace uGE{

    class ZombieController : public Controller
    {
        public:
            ZombieController(uGE::GameObject * parent);
            virtual ~ZombieController();
            //add stuff underneath here

            void update();
            void healthCheck();

        protected:
        //able to see as in public but unusable

        private:
        //don't let other mess with yo stuff


    };

}//end of uGE
#endif // ZOMBIECONTROLLER_H
