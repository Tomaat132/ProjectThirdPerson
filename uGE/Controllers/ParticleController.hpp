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
		public:
			ParticleController( GameObject * parent, GameObject * followee );
			virtual ~ParticleController();

			void update();
	};
}
#endif // ParticleController

