#ifndef SPIRITCONTROLLER_H
#define SPIRITCONTROLLER_H
#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"
#include "Player.hpp"

namespace uGE {

	class SpiritController : public Controller
	{
        private:
			uGE::Player * _followee;
			float _timeTillEmit;
			float _emitTime;
			float _innerLength;
			glm::vec3 _velocity;
			glm::vec3 _distortion;
            float _percentSucked;
            bool _targeted;
            glm::vec3 _startPos;
			std::vector < GameObject* > _particles;

		public:
			SpiritController( uGE::GameObject * parent, uGE::Player * followee);
			virtual ~SpiritController();

			void update();
			void getSucked();
			void emit(glm::vec3 aDir, float aSpd);
			void isTargeted(bool value);
            void die();

	};
}
#endif // WASDCONTROLLER_HPP
