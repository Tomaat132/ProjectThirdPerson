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
			int getColliderType();

		protected:
            GameObject * parent;

            int cType = 0;
	};
}
#endif // COLLIDER_H
