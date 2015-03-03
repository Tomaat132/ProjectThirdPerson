#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

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

	};
}
#endif // PLAYERCONTROLLER_H
