#ifndef COLLIDER_H
#define COLLIDER_H

#include "glm.hpp"

namespace uGE {

    class GameObject;
	class Collider
	{

		public:
		    enum Type {
                NONE = 0,
                SPHERE,
                AABB,
                BOX,
            };

			Collider(GameObject * aParent, std::string aName = "Collider");
			virtual ~Collider();

			glm::vec3 getPosition();
			int getColliderType();
			GameObject* getParent();
			std::string getName();

		protected:
            GameObject * parent;
            std::string name;

            int cType = 0;
	};
}
#endif // COLLIDER_H
