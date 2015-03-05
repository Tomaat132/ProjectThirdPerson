#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "Camera.hpp"

#include "Time.hpp"
#include <iostream>
#include <stdlib.h>
namespace uGE {
	ParticleController::ParticleController( uGE::GameObject * parent, GameObject * followee )
	:	Controller( parent ), _followee( followee )
	{
        _destroyTime = 0.4f;
	}

	ParticleController::~ParticleController()
	{
		//dtor
	}

	void ParticleController::update()
	{
        _destroyTime -= Time::step();

        Camera * camera = SceneManager::_camera;
        glm::mat4 & transform = _parent->transform;     //We need to optimize this mess at some point
        transform[1] = camera->transform[2];
        transform[2] = camera->transform[0];
        transform[0] = camera->transform[1];
		transform = glm::rotate( transform, -90.f, glm::vec3(1,0,0) );

		if( _destroyTime <= 0.0f ) SceneManager::del(_parent);
	}
}

