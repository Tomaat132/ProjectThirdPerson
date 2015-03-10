#ifndef ZOMBIECONTROLLER_H
#define ZOMBIECONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"

namespace uGE {

	class ZombieController : public Controller
	{
        private:
			GameObject * _followee;


		public:
			ZombieController( uGE::GameObject * parent, uGE::GameObject * followee);
			virtual ~ZombieController();

			void update();
            void die();

	};
}
#endif // ZOMBIECONTROLLER_H
