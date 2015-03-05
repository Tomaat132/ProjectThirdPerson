#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

    struct CollisionResult;
	class PlayerController : public Controller
	{
        private:
            float _shootTime;
		public:
			PlayerController( uGE::GameObject * parent );
			virtual ~PlayerController();

			void update();
			void shoot();
            void createParticle();

            void onCollision( CollisionResult * result );
	};
}
#endif // PLAYERCONTROLLER_H
