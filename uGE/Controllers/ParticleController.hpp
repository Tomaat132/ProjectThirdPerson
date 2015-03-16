#ifndef PARTICLECONTROLLER_H
#define PARTICLECONTROLLER_H

#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class ParticleController : public Controller
	{
		private:
			GameObject * _followee;
			float _destroyTime;
			glm::vec3 _direction;
			float _speed;
		public:
			ParticleController( GameObject * parent, GameObject * followee, glm::vec3 dir, float spd );
			virtual ~ParticleController();

			void update();
	};
}
#endif // ParticleController

