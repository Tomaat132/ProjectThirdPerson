#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "Camera.hpp"
#include "Body.hpp"
#include "Material.hpp"

#include "Time.hpp"
#include <iostream>
#include <stdlib.h>
namespace uGE {
	ParticleController::ParticleController( uGE::GameObject * parent, GameObject * followee, glm::vec3 dir, float spd )
	:	Controller( parent ), _followee( followee ), _direction ( dir ), _speed ( spd )
	{

        _destroyTime = 1.0f;
       // srand(time(NULL));
	}

	ParticleController::~ParticleController()
	{
		//dtor
	}

    float _randRot = rand()%4;
	void ParticleController::update()
	{

        _destroyTime -= Time::step();
        glm::mat4 & transform = _parent->transform;

       /* transform[1] = _followee->transform[2];
        transform[2] = _followee->transform[0];
        transform[0] = _followee->transform[1];
        transform = glm::translate( transform,  glm::vec3(-1.f ,0,0) * _speed * Time::step() );
*/
        Camera * camera = SceneManager::_camera;
        transform[1] = camera->transform[2];
        transform[2] = camera->transform[0];
        transform[0] = camera->transform[1];
		transform = glm::rotate( transform, -90.f, glm::vec3(1,0,0) );
        transform = glm::rotate( transform, _randRot*Time::now(), glm::vec3(0,0,1) );
        _parent->setPosition(_parent->getPosition() + _direction * _speed * Time::step());
		if( _destroyTime <= 0.0f ) SceneManager::del(_parent);

		_parent->getBody()->getMaterial()->setAlpha(_destroyTime*2);
	}
}

