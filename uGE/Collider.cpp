#include "Collider.hpp"
#include "GameObject.hpp"

namespace uGE {

	Collider::Collider( GameObject * aParent, std::string aName )
	:parent( aParent ), name( aName )
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


	int Collider::getColliderType(){

    return cType;
	}

	GameObject* Collider::getParent()
	{
	    return parent;
	}

    std::string Collider::getName()
    {
        return name;
    }
}
