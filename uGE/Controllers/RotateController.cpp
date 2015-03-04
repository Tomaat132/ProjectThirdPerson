#include "RotateController.hpp"
#include "Utils/glm.hpp"
#include "Time.hpp"

#include "GameObject.hpp"
namespace uGE {

	RotateController::RotateController( uGE::GameObject * parent )
	:	Controller( parent )
	{
		//ctor
	}

	RotateController::~RotateController()
	{
		//dtor
	}

	void RotateController::update()
	{
		glm::mat4 & transform = _parent->transform;
		transform = glm::rotate( transform, 1.f * Time::step(), glm::vec3( 0,1,0 ) );
	}
}
