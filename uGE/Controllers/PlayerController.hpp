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
			Viking * _viking;
            float _shootTime;
            bool _isWalking;
			bool _isSucking;
            bool _isAttacking;
            bool _isShooting;
            float _vikingTime;

            float zombieHitTime = 1;
            float zombieHitReset = 1;

            float regenerateHpT = 10;
            float regenerateMax = 3;

            void regenerate();

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
