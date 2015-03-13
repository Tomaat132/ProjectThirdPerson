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
        private:
            bool _viking;

		protected:

		public:
			Zombie( std::string name );
			virtual ~Zombie();

            void update();
            void setViking(bool value);
            bool getViking();

	};
}
#endif // ZOMBIE_H
