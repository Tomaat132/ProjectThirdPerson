#include "Collider.hpp"
#include "GameObject.hpp"

namespace uGE {

	Collider::Collider( GameObject * aParent )
	:parent( aParent )
	{
		//ctor
	}

	Collider::~Collider()
	{
		//dtor
	}

	glm::vec3 Collider::getPosition()
	{
        return parent->getPosition();
	}
}
