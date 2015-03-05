#include "BulletController.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "Time.hpp"

namespace uGE {
	BulletController::BulletController( GameObject * parent, GameObject * shooter)
	:	Controller( parent ), _shooter( shooter )
	{
	    _destroyTime = 0.5f;
	    _speed = 100.f;
	    _direction = _shooter->getDirection(); // Uses his own direction - the actual gameobject should have direction
       // std::cout<< _parent->getName() << std::endl;

	}

	BulletController::~BulletController()
	{
		//dtor
	}

	void BulletController::update()
	{
	    _destroyTime -= Time::step();
       // std::cout<< _direction << std::endl;
	    _parent->transform = glm::translate( _parent->transform, _direction * _speed * Time::step() );
	    //_parent->setPosition( _followee->getPosition() + glm::vec3( 0.f, 10.f, -15.f ) );
		//glm::mat4 & transform = _parent->transform;
		//transform = glm::inverse( glm::lookAt( glm::vec3( transform[3] ), glm::vec3( _followee->transform[3] ), glm::vec3( 0,1,0 ) ) );
		if( _destroyTime <= 0.0f ) { uGE::SceneManager::del(_parent); }
	}
}
