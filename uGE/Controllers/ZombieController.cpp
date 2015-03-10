#include <SFML/Window.hpp>
#include "ZombieController.hpp"
#include "SceneManager.hpp"
#include "AssetManager.hpp"
#include "ParticleController.hpp"
#include "GameObject.hpp"
#include "Body.hpp"
#include "Animation.hpp"
#include "Material.hpp"
#include "Time.hpp"
#include "Camera.hpp"

namespace uGE {

	ZombieController::ZombieController( uGE::GameObject * parent, uGE::GameObject * followee)
	:	Controller( parent ), _followee( followee )
	{

	}

	ZombieController::~ZombieController()
	{

	}

	void ZombieController::update()
	{

	}


	void ZombieController::die()
	{
        SceneManager::del(_parent);
	}
}
