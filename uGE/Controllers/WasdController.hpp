#ifndef WASDCONTROLLER_HPP
#define WASDCONTROLLER_HPP
#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class WasdController : public Controller
	{
		public:
			WasdController( uGE::GameObject * parent );
			virtual ~WasdController();

			void update();
	};
}
#endif // WASDCONTROLLER_HPP
