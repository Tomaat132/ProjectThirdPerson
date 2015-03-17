#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "Viking.hpp"

#include "Player.hpp"

namespace uGE {

    struct CollisionResult;
    class Player;
	class PlayerController : public Controller
	{
        private:
            uGE::Player* _parent;
            float _shootTime;
            bool _isSucking;
            float _vikingTime;

            float zombieHitTime = 1;
            float zombieHitReset = 1;

            float regenerateHpT = 10;
            float regenerateMax = 3;

            void regenerate();

            Viking * _viking;

		public:
			PlayerController( uGE::Player * parent );
			virtual ~PlayerController();

			void update();
			void shoot();
			void attack();
			void vacuum();
            void releaseButton();
            void onCollision( CollisionResult * result );
	};
}
#endif // PLAYERCONTROLLER_H
