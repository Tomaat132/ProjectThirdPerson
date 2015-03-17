#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>
#include <vector>
#include "utils/glm.hpp"
#include "ZombieController.hpp"
#include "Shader.hpp"

typedef std::vector<uGE::Mesh*> Anim;

namespace uGE {

	class Body;
	class Collider;
	class Controller;
	class Material;
	class Zombie : public GameObject
	{
        private:
            bool _viking;

            float time = 0.f;
            unsigned int frame = 0;
            std::string activeAction;
            Anim idle;
            Anim walk;
            Anim attack;
            Anim death;
            Anim currentAnim;


		protected:

		public:
			Zombie( std::string name );
			virtual ~Zombie();

            void update();
            void playNow( std::string action );
            void updateFrame();
            void setViking(bool value);
            bool getViking();

	};
}
#endif // ZOMBIE_H
