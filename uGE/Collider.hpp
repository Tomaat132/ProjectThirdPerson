#ifndef COLLIDER_H
#define COLLIDER_H

#include "glm.hpp"

namespace uGE {

    class GameObject;

	class Collider
	{

		public:
			Collider(GameObject * aParent);
			virtual ~Collider();

			glm::vec3 getPosition();

		protected:
            GameObject * parent;

	};
}
#endif // COLLIDER_H
