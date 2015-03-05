#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"

#include "Time.hpp"
#include <iostream>
#include <stdlib.h>
namespace uGE {
	ParticleController::ParticleController( uGE::GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
        _destroyTime = 0.04f;
        _rotation = float(rand()*0.1f);
	}

	ParticleController::~ParticleController()
	{
		//dtor
	}

	void ParticleController::update()
	{
        _destroyTime -= Time::step();

		glm::mat4 & transform = _parent->transform;

        //std::cout<< transform << std::endl;
		transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		transform = glm::rotate( transform, -180.f, glm::vec3(1,0,0) );

        transform = glm::rotate( transform, _rotation, glm::vec3( 0,0,1 ) );

		if( _destroyTime <= 0.0f ) uGE::SceneManager::del(_parent);

	}
}

