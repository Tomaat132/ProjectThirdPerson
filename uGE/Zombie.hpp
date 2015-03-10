#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <vector>
#include "utils/glm.hpp"
#include "ZombieController.hpp"
#include "Shader.hpp"


namespace uGE {

	class Body;
	class Collider;
	class Controller;
	class Material;
	class Zombie : public GameObject
	{
        public:
            bool targeted;
		protected:

			//SpiritController * _controller;

		public:
			Zombie( std::string name );
			virtual ~Zombie();

            void update();

	};
}
#endif // ZOMBIE_H
