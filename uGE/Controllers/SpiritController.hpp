#ifndef SPIRITCONTROLLER_H
#define SPIRITCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"

namespace uGE {

	class SpiritController : public Controller
	{
        private:
			GameObject * _followee;
			float _timeTillEmit;
			float _emitTime;
			glm::vec3 _velocity;
			glm::vec3 _distortion;
            float _percentSucked;
            bool _targeted;

			std::vector < GameObject* > _particles;

		public:
			SpiritController( uGE::GameObject * parent, uGE::GameObject * followee);
			virtual ~SpiritController();

			void update();
			void getSucked();
			void emit();
			void isTargeted(bool value);
            void die();

	};
}
#endif // WASDCONTROLLER_HPP
