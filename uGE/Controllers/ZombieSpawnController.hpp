#ifndef ZOMBIESPAWNCONTROLLER_H
#define ZOMBIESPAWNCONTROLLER_H

#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"
#include "Zombie.hpp"
namespace uGE {

	class ZombieSpawnController : public Controller
	{
		private:
			GameObject * _followee;
			float _timeTillSpawn;
			float _spawnTime;
			float _maxZombies;
            float _zombieLvlUpTimer;
        public:
            static std::vector< Zombie* > zombies;
        private:
            void spawn();
		public:
			ZombieSpawnController( GameObject * parent, GameObject * followee );
			virtual ~ZombieSpawnController();

			void update();
	};
}
#endif // ZombieSpawnController

