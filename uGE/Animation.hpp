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
        private:
            GLuint _name;
		    GLuint _buffTotal[2]; //total buffers
			std::vector< glm::vec3 > _animTrans; // all translations
			std::vector< glm::vec3 > _animRot; // all rotations

		public:
			Animation();
			virtual ~Animation();

			GLuint getTransBuffer();
			GLuint getRotBuffer();
			unsigned int size();

			static Animation * LoadAnimation(std::string filename);
			void PlayAnimation();

		private:
		    GLuint createBuffers();
	};
}
#endif // ANIMATION_H
