#include "ParticleController.hpp"
#include "GameObject.hpp"
#include <iostream>
namespace uGE {
	ParticleController::ParticleController( uGE::GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
	}

	ParticleController::~ParticleController()
	{
		//dtor
	}

	void ParticleController::update()
	{
		glm::mat4 & transform = _parent->transform;
        //std::cout<< transform << std::endl;
		transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		transform[2] *= -1;
	}
}

