#ifndef SPIRITCONTROLLER_H
#define SPIRITCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"

namespace uGE {

	class SpiritController : public Controller
	{
        private:
            GameObject * _particleEmitter;
			GameObject * _followee;
            float _percentSucked;

		public:
			SpiritController( uGE::GameObject * parent, uGE::GameObject * followee);
			virtual ~SpiritController();

			void update();
			void getSucked();
	};
}
#endif // WASDCONTROLLER_HPP
