#include "Utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"
#include "CollisionDetection.hpp"

namespace uGE {

	Controller::Controller( GameObject * parent )
	:	_parent( parent )
	{
		parent->setController( this );
	}

	Controller::~Controller()
	{
	}

	GameObject* Controller::getParent()
	{
	    return _parent;
	}

	void Controller::onCollision( CollisionResult * result ) {}
}
