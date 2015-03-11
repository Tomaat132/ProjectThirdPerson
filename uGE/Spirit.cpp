#include "GameObject.hpp"
#include "Spirit.hpp"
#include "Animation.hpp"
#include "Body.hpp"
#include "Collider.hpp"
#include "Controller.hpp"
#include "SpiritController.hpp"
#include "Material.hpp"
#include "Renderer.hpp"


namespace uGE {

	Spirit::Spirit( std::string name )
	: GameObject( name )
	{
	    targeted = false;
	    //_direction = glm::vec3(1f, 0f, 0f);
	}

	Spirit::~Spirit()
	{
		//GameObject::~GameObject();
	}

	void Spirit::update()
	{
		GameObject::update();
	}


	void Spirit::isTargeted( bool value) {
	    targeted = value;
        SpiritController* controller = dynamic_cast<SpiritController*> ( _controller );
        controller->isTargeted( targeted);
	}
}
