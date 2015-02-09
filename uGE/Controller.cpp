#include "Utils/glm.hpp"
#include "Controller.hpp"
#include "GameObject.hpp"

namespace uGE {

	Controller::Controller( GameObject * parent )
	:	_parent( parent )
	{
		parent->setController( this );
	}

	Controller::~Controller()
	{
	}
}
