#ifndef PARTICLEEMITTERCONTROLLER_H
#define PARTICLEEMITTERCONTROLLER_H

#include "utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"

namespace uGE {

	class ParticleEmitterController : public Controller
	{
		private:
			GameObject * _followee;
			float _timeTillEmit;
			float _emitTime;
			glm::vec3 _velocity;
			glm::vec3 _distortion;

			std::vector < GameObject* > _particles;
        private:
            void emit();
		public:
			ParticleEmitterController( GameObject * parent, GameObject * followee );
			virtual ~ParticleEmitterController();

			void update();
			void setVelocity(glm::vec3 aVelocity);
			void setDistortion(glm::vec3 aVelocity);
			void getSucked();
	};
}
#endif // ParticleEmitterController

