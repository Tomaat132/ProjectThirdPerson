#ifndef SPIRIT_H
#define SPIRIT_H

#include <string>
#include <vector>
#include "utils/glm.hpp"
#include "SpiritController.hpp"
#include "Shader.hpp"


namespace uGE {

	class Body;
	class Collider;
	class Controller;
	class Material;
	class Spirit : public GameObject
	{
        public:
            bool targeted;
		protected:

			//SpiritController * _controller;

		public:
			Spirit( std::string name );
			virtual ~Spirit();

            void update();
            void isTargeted(bool value);

	};
}
#endif // SPIRIT_H
