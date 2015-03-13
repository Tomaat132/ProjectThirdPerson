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
	    _destroyTime -= Time::step();
	    _parent->transform = glm::translate( _parent->transform, _direction * _speed * Time::step() );
        if( _destroyTime <= 0.0f ) {
			uGE::SceneManager::del(_parent);
		}
	}
}
