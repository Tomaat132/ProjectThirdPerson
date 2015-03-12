#include "GameObject.hpp"
#include "Zombie.hpp"
#include "Animation.hpp"
#include "Body.hpp"
#include "Collider.hpp"
#include "Controller.hpp"
#include "ZombieController.hpp"
#include "Material.hpp"
#include "Renderer.hpp"


namespace uGE {

	Zombie::Zombie( std::string name )
	: GameObject( name )
	{
	    //targeted = false;
	    //_direction = glm::vec3(1f, 0f, 0f);
	}

	Zombie::~Zombie()
	{
		//GameObject::~GameObject();
	}

	void Zombie::update()
	{
		GameObject::update();
	}
}
