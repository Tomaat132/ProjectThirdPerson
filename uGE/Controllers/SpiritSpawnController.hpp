#ifndef SPIRITSPAWNCONTROLLER_H
#define SPIRITSPAWNCONTROLLER_H

#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"
#include "Spirit.hpp"
namespace uGE {

	class SpiritSpawnController : public Controller
	{
		private:
			GameObject * _followee;
			float _timeTillSpawn;
			float _spawnTime;

        public:
             static std::vector < Spirit* > spirits;

        private:
            void spawn();
		public:
			SpiritSpawnController( GameObject * parent, GameObject * followee );
			virtual ~SpiritSpawnController();

			void update();
	};
}
#endif // SpiritSpawnController

