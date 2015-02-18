#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class PlayerController : public Controller
	{
		public:
			PlayerController( uGE::GameObject * parent );
			virtual ~PlayerController();

			void update();
	};
}
#endif // PLAYERCONTROLLER_H
