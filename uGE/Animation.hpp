#ifndef ANIMATION_H
#define ANIMATION_H

#include <fstream>
#include <iostream>
#include <string>

#include "Body.hpp"
#include "Utils/glm.hpp"

namespace uGE {


	class Animation
	{
		public:
			Animation(GameObject * _parent);
			virtual ~Animation();

			static Animation * LoadAnimation(std::string filename);
			void PlayAnimation();

		protected:
            glm::vec3 aniTrans[];
            glm::vec3 aniRot[];

		private:
		    GameObject * _parent;
	};
}
#endif // ANIMATION_H
