#ifndef BULLETCONTROLLER_H
#define BULLETCONTROLLER_H

#include "utils/glm.hpp"
#include "Controller.hpp"

namespace uGE {

	class BulletController : public Controller
	{
		private:
			GameObject * _shooter;
			glm::vec3 _direction;
            float _speed;
            float _destroyTime;
		public:
			BulletController( GameObject * parent, GameObject * shooter);
			virtual ~BulletController();

			void update();
			bool isGreaterThan(glm::vec3 input1, glm::vec3 input2);
	};
}
#endif // BULLETCONTROLLER_H
