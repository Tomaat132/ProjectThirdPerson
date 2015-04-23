#include "BulletController.hpp"
#include "GameObject.hpp"
#include "SceneManager.hpp"
#include "Time.hpp"

namespace uGE {
	BulletController::BulletController( GameObject * parent, GameObject * shooter)
	:	Controller( parent ), _shooter( shooter )
	{
	    _destroyTime = 2.f;//.5f
	    _speed = 15.f;//100.f
	    _direction = _shooter->getDirection(); // Uses his own direction - the actual gameobject should have direction
	}

	BulletController::~BulletController()
	{
		//dtor
	}

	void BulletController::update()
	{
	    glm::mat4 & transform = _parent->transform;
	    //transform = glm::rotate( transform, 1.f*Time::step(), glm::vec3( 0,0,1 ) );

	    _parent->setRotation(_direction );


	    _destroyTime -= Time::step();
	    _parent->transform = glm::translate( _parent->transform, glm::vec3( sin(_destroyTime*15)/5, 0 ,1 ) * _speed * Time::step() );
        if( _destroyTime <= 0.0f ) {
			uGE::SceneManager::del(_parent);
		}
	}
}
