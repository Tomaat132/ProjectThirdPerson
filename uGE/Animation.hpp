#ifndef ANIMATION_H
#define ANIMATION_H

#include <fstream>
#include <iostream>
#include <string>

#include "GameObject.hpp"
#include "Body.hpp"
#include "Utils/glm.hpp"

namespace uGE {


	class Animation
	{
        private:
            bool isPlaying;
            int frame;
            bool _repeat;
            GameObject * _parent;
            Mesh * _mesh;
            GLuint _name;
		    GLuint _buffTotal[2]; //total buffers
			std::vector< glm::vec3 > _animTrans; // all translations
			std::vector< glm::vec3 > _animRot; // all rotations

		protected:
            glm::mat4 _animTransform;

		public:
			Animation();
			virtual ~Animation();

			GLuint getTransBuffer();
			GLuint getRotBuffer();
			unsigned int size();

            void setMesh( Mesh * mesh );
			static Animation * LoadAnimation(std::string filename);
			void PlayAnimation(GameObject * parent, bool repeat);
            void update();

		private:
		    GLuint createBuffers();
	};
}
#endif // ANIMATION_H
